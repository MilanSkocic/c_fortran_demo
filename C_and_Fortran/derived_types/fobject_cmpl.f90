module fobject_cmpl
    use iso_fortran_env
    use iso_c_binding
    implicit none

    ! Complex case where the Fortran derived can not be mapped directly
    ! This is the case when there are pointers and bound-procedures
    ! The trick is to pass the derived type to C as pointer (void *)
    ! wrap all bound procedures with procedures that will accept a C pointer void*

    type :: fobj_cmpl
        integer(int32) :: n
        real(real32), pointer :: array(:)
    contains
        procedure :: print => fobj_cmpl_print
    end type

contains

subroutine fobj_cmpl_print(self)
    implicit none
    class(fobj_cmpl), intent(in) :: self
    print *, self%n
    print *, self%array
end subroutine

subroutine fobj_cmpl_del(o)
    implicit none
    type(fobj_cmpl), intent(inout), pointer :: o
    deallocate(o%array)
    deallocate(o)
end subroutine

pure function fobj_cmpl_init(n, value)result(p)
    implicit none
    integer(int32), intent(in) :: n
    real(real32), intent(in) :: value
    type(fobj_cmpl), pointer :: p
    
    allocate(p)
    allocate(p%array(n))
    
    p%n = n
    p%array = value
end function

subroutine fobj_cmpl_capi_print(o)bind(c)
    implicit none
    type(c_ptr), intent(in), value :: o
    type(fobj_cmpl), pointer :: fp
    nullify(fp)
    call c_f_pointer(o, fp)
    call fp%print()
end subroutine

subroutine fobj_cmpl_capi_del(o)bind(c)
    implicit none
    type(c_ptr), intent(in), value :: o
    type(fobj_cmpl), pointer :: fp
    nullify(fp)
    call c_f_pointer(o, fp)
    call fobj_cmpl_del(fp)
end subroutine

pure function fobj_cmpl_capi_init(n, value)result(p)bind(c)
    implicit none
    integer(c_int), intent(in), value :: n
    real(c_float), intent(in), value :: value

    type(c_ptr) :: p

    type(fobj_cmpl), pointer :: fp
    fp => fobj_cmpl_init(n, value)
    p = c_loc(fp)
end function

end module