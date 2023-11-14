program main
  use rtvl_module
  use matmul_module
  implicit none
  double precision, allocatable :: a(:,:), b(:,:), c(:,:)
  integer :: n, r = 1, rn, i, j, m
  logical :: ok
  double precision :: size
  character(len=32) :: arg

  if (command_argument_count() == 1) then
    call get_command_argument(1, arg)
    read(arg, *) n
  else
    call get_command_argument(1, arg)
    read(arg, *) r
    call get_command_argument(2, arg)
    read(arg, *) n
  end if

  rn = rtvl(n)

  allocate(a(rn,n), b(rn,n), c(rn,n))

  do i = 1, n
    do j = 1, n
      c(i,j) = 1.0d0/sqrt(dble(i)) + 1.0d0/sqrt(dble(j))
      b(i,j) = merge(1, 0, i == j)
    end do
  end do

  do m = 1, r
    call matmul(a, b, c, n)
  end do

  ok = .true.
  do i = 1, n
    do j = 1, n
      ok = ok .and. abs(a(i,j) - c(i,j)) < 0.001d0*(abs(a(i,j)) + abs(c(i,j)))
    end do
  end do

  print*, "Ok = ", ok

  deallocate(a, b, c)

end program main
