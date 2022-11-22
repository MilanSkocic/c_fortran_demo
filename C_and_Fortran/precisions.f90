!>
!! @file


!>
!! @brief Precision module
module precision
    use iso_c_binding

    integer(c_int) :: dp = kind(c_double) !< Double precision.
    integer(c_int) :: sp = kind(c_float)  !< Simple precision


end module precision