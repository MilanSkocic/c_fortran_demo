module f_func


    interface
        ! C function prototype
        subroutine c_func(C, m, n) bind(C)
            use iso_c_binding
            integer(c_int), intent(in) :: m
            integer(c_int), intent(in) :: n
            real(c_double), intent(in), dimension(m, n) :: C
        end subroutine
        subroutine colmajor_to_rowmajor(C, m, n, R) bind(C)
            use iso_c_binding
            integer(c_int), intent(in) :: m
            integer(c_int), intent(in) :: n
            real(c_double), intent(in), dimension(m, n) :: C
            real(c_double), intent(out), dimension(m, n) :: R
        end subroutine
        subroutine c_print_string(char_p) bind(c)
            use iso_c_binding, only : c_ptr
            type(c_ptr), intent(in), value :: char_p
        end subroutine

    end interface

contains

        function f2c_string(f_string)
            use iso_c_binding, only : c_char, c_ptr, c_loc, c_null_char
            character(len=*), intent(in), target :: f_string
            character(len=len(f_string)+1, kind=c_char), target :: c_string
            type(c_ptr):: f2c_string
            c_string = f_string // c_null_char
            f2c_string = c_loc(c_string)
        end function

        function c2f_string(char_p, length) 
            use iso_c_binding, only :c_int, c_ptr, c_f_pointer
            integer(c_int), intent(in), value :: length
            type(c_ptr), intent(in), value :: char_p
            character, pointer, dimension(:) :: c2f_string
            call c_f_pointer(char_p, c2f_string, shape=[length+1])
        end function

        subroutine f_print(char_p, length)bind(c)
            use iso_c_binding, only :c_int, c_ptr
            integer(c_int), intent(in), value :: length
            type(c_ptr), intent(in), value :: char_p
            print *, c2f_string(char_p, length)
        end subroutine


end module f_func