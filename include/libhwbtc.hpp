#pragma once

#include <libhwbtc.h>
#include <stdexcept>

namespace libhwbtc
{
    /*! \cond */
    inline void throw_if_needed(libhwbtc_error * err);
    /*! \endcond */

    /*! Wrapper for libhwbtc_error_free(). */
    inline void pointer_free(libhwbtc_error * p) noexcept
    {
        libhwbtc_error_free(p);
    }

    /*! Wrapper for libhwbtc_error_copy(). */
    inline libhwbtc_error * pointer_copy(libhwbtc_error * p) noexcept
    {
        return libhwbtc_error_copy(p);
    }

    /*! This class is not part of the public API of the library and you should
     * not use it directly, but you can use the public methods it provides to
     * the classes that inherit from it.
     *
     * For any type T, if you define pointer_free(T *), then
     * unique_pointer_wrapper<T> will be a well-behaved C++ class that provides
     * a constructor, implicit conversion to a bool, C++ move operations,
     * pointer operations, and forbids C++ copy operations. */
    template<class T>
    class unique_pointer_wrapper
    {
    public:
        /*! Constructor that takes a pointer. */
        explicit unique_pointer_wrapper(T * p = NULL) noexcept : pointer(p)
        {
        }

        /*! Move constructor. */
        unique_pointer_wrapper(unique_pointer_wrapper && other) noexcept
        {
            pointer = other.pointer_release();
        }

        /*! Move assignment operator. */
        unique_pointer_wrapper & operator=(unique_pointer_wrapper && other) noexcept
        {
            pointer_reset(other.pointer_release());
            return *this;
        }

        /*! Destructor. */
        ~unique_pointer_wrapper() noexcept
        {
            pointer_reset();
        }

        /*! Implicit conversion to bool.  Returns true if the underlying pointer
         *  is not NULL. */
        operator bool() const noexcept
        {
            return pointer != NULL;
        }

        /*! Returns the underlying pointer. */
        T * pointer_get() const noexcept
        {
            return pointer;
        }

        /*! Sets the underlying pointer to the specified value, freeing the
         * previous pointer and taking ownership of the specified one. */
        void pointer_reset(T * p = NULL) noexcept
        {
            pointer_free(pointer);
            pointer = p;
        }

        /*! Releases the pointer, transferring ownership of it to the caller and
         * resetting the underlying pointer of this object to NULL.  The caller
         * is responsible for freeing the returned pointer if it is not NULL. */
        T * pointer_release() noexcept
        {
            T * p = pointer;
            pointer = NULL;
            return p;
        }

        /*! Returns a pointer to the underlying pointer. */
        T ** pointer_to_pointer_get() noexcept
        {
            return &pointer;
        }

        /*! Copy constructor: forbid. */
        unique_pointer_wrapper(const unique_pointer_wrapper & other) = delete;

        /*! Copy assignment operator: forbid. */
        unique_pointer_wrapper & operator=(const unique_pointer_wrapper & other) = delete;

    protected:
        /*! The underlying pointer that is being wrapped.  This pointer will be
         * freed when the object is destroyed. */
        T * pointer;
    };

    /*! This class is not part of the public API of the library and you should
     * not use it directly, but you can use the public methods it provides to
     * the classes that inherit from it.
     *
     * For any type T, if you define pointer_free(T *) and pointer_copy(T *), then
     * unique_pointer_wrapper_with_copy<T> will be a well-behaved C++ class that provides
     * a constructor, implicit conversion to a bool, C++ move operations, C++ copy operations,
     * and pointer operations. */
    template <class T>
    class unique_pointer_wrapper_with_copy : public unique_pointer_wrapper<T>
    {
    public:
        /*! Constructor that takes a pointer. */
        explicit unique_pointer_wrapper_with_copy(T * p = NULL) noexcept
            : unique_pointer_wrapper<T>(p)
        {
        }

        /*! Move constructor. */
        unique_pointer_wrapper_with_copy(
            unique_pointer_wrapper_with_copy && other) noexcept = default;

        /*! Copy constructor */
        unique_pointer_wrapper_with_copy(
            const unique_pointer_wrapper_with_copy & other)
        {
            this->pointer = pointer_copy(other.pointer);
        }

        /*! Copy assignment operator. */
        unique_pointer_wrapper_with_copy & operator=(
          const unique_pointer_wrapper_with_copy & other)
        {
            this->pointer_reset(pointer_copy(other.pointer));
            return *this;
        }

        /*! Move assignment operator. */
        unique_pointer_wrapper_with_copy & operator=(
            unique_pointer_wrapper_with_copy && other) noexcept = default;
    };

    /*! Wrapper for a ::libhwbtc_error pointer. */
    class error : public unique_pointer_wrapper_with_copy<libhwbtc_error>, public std::exception
    {
    public:
        /*! Constructor that takes a pointer.  */
        explicit error(libhwbtc_error * p = NULL) noexcept :
          unique_pointer_wrapper_with_copy(p)
        {
        }

        /*! Wrapper for libhwbtc_error_get_message(). */
        virtual const char * what() const noexcept
        {
            return libhwbtc_error_get_message(pointer);
        }

        /*! Wrapper for libhwbtc_error_get_message() that returns a
         *  std::string. */
        std::string message() const
        {
            return what();
        }

        /*! Wrapper for libhwbtc_error_has_code(). */
        bool has_code(uint32_t error_code) const noexcept
        {
            return libhwbtc_error_has_code(pointer, error_code);
        }
    };

    /*! \cond */
    inline void throw_if_needed(libhwbtc_error * err)
    {
        if (err != NULL)
        {
            throw error(err);
        }
    }
    /*! \endcond */
}
