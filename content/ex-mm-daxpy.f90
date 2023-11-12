module matmul_module
  use rtvl_module
  implicit none
contains
  subroutine matmul(a, b, c, n)
    integer, intent(in) :: n
    double precision, intent(inout) :: a(rtvl(n),n)
    double precision, intent(in) :: b(rtvl(n),n), c(rtvl(n),n)
    integer :: i, j, k

    do j = 1, n
      a(1:n,j) = 0
      do k = 1, n
        do i = 1, n
          a(i,j) = a(i,j) + b(i,k) * c(k,j)
        end do
      end do
    end do
  end subroutine matmul
end module matmul_module
