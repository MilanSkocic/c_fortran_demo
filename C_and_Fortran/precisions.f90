!>
!! @file


!>
!! @brief Precision module
module precision
    use iso_c_binding
    implicit none

    integer, parameter :: dp = kind(c_double) !< Double precision.
    integer, parameter :: sp = kind(c_float)  !< Simple precision

    real(kind=dp), protected :: pi = 4*atan(1.0_dp)

    !> @brief Point type
    type :: point
        real :: x !< x coordinates
        real :: y !< y coordinates
    end type

end module precision