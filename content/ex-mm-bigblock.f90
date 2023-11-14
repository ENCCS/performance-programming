module matmul_module
  use rtvl_module
  implicit none
contains
  subroutine matmul(a, b, c, n)
    integer, intent(in) :: n
    double precision, intent(inout) :: a(rtvl(n),n)
    double precision, intent(in) :: b(rtvl(n),n), c(rtvl(n),n)
    integer :: i, j, k, rn, m, ib, kb, ii, kk, ilim, klim
    double precision :: c00, c10, c20, c30, c01, c11, c21, c31
    double precision :: s0, s1

    rn = rtvl(n)
    m = mod(n, 4)

    ib = merge(512, n, n > 512)
    kb = merge(4 * (1024 / ib), 16, n < 256)

    do ii = 1, n, ib
      ilim = min(ii+ib-1, n)
      do kk = 1, n, kb
        klim = min(kk+kb-1, n)
        do j = 1, n, 2
          if (kk == 1) then
            a(ii:ilim,j:j+1) = 0
          end if
          do k = kk, klim-3, 4
            c00 = c(k,  j)
            c10 = c(k+1,j)
            c20 = c(k+2,j)
            c30 = c(k+3,j)
            c01 = c(k,  j+1)
            c11 = c(k+1,j+1)
            c21 = c(k+2,j+1)
            c31 = c(k+3,j+1)
            do i = ii, ilim
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
          if (klim == n) then
            do k = n-m+1, n
              do i = ii, ilim
                a(i,j)  = a(i,j)   + b(i,k) * c(k,j)
                a(i,j+1)= a(i,j+1) + b(i,k) * c(k,j+1)
              end do
            end do
          end if
        end do
      end do
    end do
  end subroutine matmul
end module matmul_module

