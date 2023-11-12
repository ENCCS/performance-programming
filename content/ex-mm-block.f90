module matmul_module
  use rtvl_module
  implicit none
contains
  subroutine matmul(a, b, c, n)
    integer, intent(in) :: n
    double precision, intent(inout) :: a(n,n)
    double precision, intent(in) :: b(n,n), c(n,n)
    integer :: i, j, k, rn, m
    double precision :: c00, c10, c20, c30, c01, c11, c21, c31
    double precision :: s0, s1

    rn = rtvl(n)
    m = mod(n, 4)

    do j = 1, n, 2
      a(1:n,j:j+1) = 0
      do k = 1, n-m, 4
        c00 = c(k,  j)
        c10 = c(k+1,j)
        c20 = c(k+2,j)
        c30 = c(k+3,j)
        c01 = c(k,  j+1)
        c11 = c(k+1,j+1)
        c21 = c(k+2,j+1)
        c31 = c(k+3,j+1)
        do i = 1, n
          s0 = a(i,j)
          s1 = a(i,j+1)
          s0 = s0 + b(i,k+0) * c00
          s1 = s1 + b(i,k+0) * c01
          s0 = s0 + b(i,k+1) * c10
          s1 = s1 + b(i,k+1) * c11
          s0 = s0 + b(i,k+2) * c20
          s1 = s1 + b(i,k+2) * c21
          s0 = s0 + b(i,k+3) * c30
          s1 = s1 + b(i,k+3) * c31
          a(i,j)   = s0
          a(i,j+1) = s1
        end do
      end do
      do k = n-m+1, n
        do i = 1, n
          a(i,j)  = a(i,j)   + b(i,k) * c(k,j)
          a(i,j+1)= a(i,j+1) + b(i,k) * c(k,j+1)
        end do
      end do
    end do
  end subroutine matmul
end module matmul_module

