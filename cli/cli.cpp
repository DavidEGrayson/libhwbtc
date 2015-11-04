#include <libhwbtc.hpp>
#include <iostream>
#include <cassert>
#include <hidapi/hidapi.h>

int main(int argc, char ** argv)
{
    std::cout << "hello there" << std::endl;

    struct hid_device_info * list = hid_enumerate(0x534c, 0x0001);

    struct hid_device_info * info = list;
    while (info != NULL)
    {
        printf("%04x:%04x %ls\n", info->vendor_id, info->product_id, info->product_string);
        break;
        info = info->next;
    }

    if (info == NULL)
    {
        std::cerr << "Error: Could not find matching device." << std::endl;
        return 1;
    }

    hid_free_enumeration(list);

    return 0;
}
