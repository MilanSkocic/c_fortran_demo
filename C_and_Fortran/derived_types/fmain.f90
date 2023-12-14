program fmain
    use fobject_simple
    use fobject_cmpl
    implicit none

    type(fobj_cmpl), pointer :: obj_cmpl

    ! SIMPLE FORTRAN DERIVED TYPE
    print *, obj_simple%n
    print *, obj_simple%array
    print *, obj_simple%name

    ! COMPLEXE FORTRAN TYPE
    obj_cmpl => fobj_cmpl_init(3, 6.2)
    
    call obj_cmpl%print()
    


    call fobj_cmpl_del(obj_cmpl)


end program