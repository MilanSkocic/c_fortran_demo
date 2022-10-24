program main
    implicit none
    external dgemm

    interface
        subroutine c_func(C, m, n)
            integer(4), intent(in) :: m
            integer(4), intent(in) :: n
            real(8), intent(in), dimension(m, n) :: C
        end subroutine
        subroutine colmajor_to_rowmajor(C, m, n, R)
            integer(4), intent(in) :: m
            integer(4), intent(in) :: n
            real(8), intent(in), dimension(m, n) :: C
            real(8), intent(out), dimension(m, n) :: R
        end subroutine

    end interface

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
    

    call dgemm(TRANSA, TRANSB, m, n, k, alpha, A, LDA, B, LDB, BETA, C, LDC)
    
    call colmajor_to_rowmajor(C, m, n, R)
    call c_func(R, m, n)
    
    do i=1, m
           print "(2F10.5, A)", C(i,:)
    end do
    

end program main