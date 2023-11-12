module matmul_module
  use rtvl_module
  implicit none
contains
  subroutine matmul(a, b, c, n)
    use rtvl_module
    implicit none
    integer, intent(in) :: n
    double precision, intent(inout) :: a(rtvl(n),n)
    double precision, intent(in) :: b(rtvl(n),n), c(rtvl(n),n)
    integer :: i, j, k
    double precision :: sum

    do i = 1, n
      do j = 1, n
        sum = 0
        do k = 1, n
          sum = sum + b(i,k) * c(k,j)
        end do
        a(i,j) = sum
      end do
    end do
  end subroutine matmul
end module matmul_module
