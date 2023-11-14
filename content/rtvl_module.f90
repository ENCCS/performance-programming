module rtvl_module
  implicit none
contains
  pure function rtvl(n)
    integer, intent(in) :: n
    integer :: rtvl

#ifdef RTVL
    rtvl = iand(n+3, -4)
#else
    rtvl = n
#endif
  end function rtvl
end module rtvl_module

