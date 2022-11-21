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
            type(c_ptr):: f2c_string
            nullify(f_string)
            f2c_string = c_loc(f_string)
        end function

        function c2f_string(char_p, length) 
            use iso_c_binding, only : c_int, c_ptr, c_f_pointer
            integer(c_int), intent(in), value :: length
            type(c_ptr), intent(in), value :: char_p
            character, pointer, dimension(:) :: c2f_string
            call c_f_pointer(char_p, c2f_string, shape=[length+1])
        end function

        pure function is_zero_terminated(f_string)
            use iso_c_binding, only : c_null_char
            character(len=*), intent(in) :: f_string
            integer :: is_zero_terminated, n
            n = len(f_string)
            is_zero_terminated = 0
            do i=1, n
                if(f_string(i:i) == c_null_char)then
                    is_zero_terminated = 1
                else
                    is_zero_terminated = 0
                end if
            end do

        end function

        subroutine f_print(char_p, length)bind(c)
            use iso_c_binding, only : c_int, c_ptr
            implicit none
            integer(c_int), intent(in), value :: length
            type(c_ptr), intent(in), value :: char_p
            print *, c2f_string(char_p, length)
        end subroutine

        subroutine nullify(f_string)
            use iso_c_binding, only : c_null_char
            implicit none
            character, pointer, intent(inout) :: f_string(:)
            integer :: n
            n = len(f_string)
            f_string(n:n) = c_null_char
        end subroutine

end module f_func