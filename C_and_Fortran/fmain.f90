program main
    use f_func
    use iso_c_binding, only : c_char, c_null_char
    implicit none
    external dgemm

    integer(kind=4) :: i, j
    integer(kind=4), parameter :: m = 5
    integer(kind=4), parameter :: k = 5
    integer(kind=4), parameter :: n = 2

    real(kind=8), dimension(m, k) :: A
    real(kind=8), dimension(k, n) :: B
    real(kind=8), dimension(m, n) :: C
    real(kind=8), dimension(m, n) :: R

    CHARACTER :: TRANSA = 'N'
    CHARACTER :: TRANSB = 'N'

    integer(kind=4) :: LDA = m
    integer(kind=4) :: LDB = k
    integer(kind=4) :: LDC = m

    real(kind=8) :: alpha = 0.1
    real(kind=8) :: BETA = 2.21

    character(len=*), parameter:: f_string = "Fortran string sent to C func which prints it"

    do i=1, m
        do j=1, k
            A(i,j) = i+j-2
        end do
    end do
    
    do i=1, k
        do j=1, n
            B(i,j) = i+j-2
        end do
    end do
    
    do i=1, m
        do j=1, n
            C(i,j) = i+j-2
            R(i,j) = 0.0
        end do
    end do

    print *, "Fortran program"
    
    print *, "Call BLAS dgemm"
    call dgemm(TRANSA, TRANSB, m, n, k, alpha, A, LDA, B, LDB, BETA, C, LDC)
    
    print *, "Call C func: colmajor_to_rowmajor"
    call colmajor_to_rowmajor(C, m, n, R)
    print *, "Call C func: print_matrix"
    call c_func(R, m, n)
    
    print *, "Print matrix in fortran."
    do i=1, m
           print "(2F10.5, A)", C(i,:)
    end do

    call c_print_string(f2c_string(f_string//c_null_char))

end program main