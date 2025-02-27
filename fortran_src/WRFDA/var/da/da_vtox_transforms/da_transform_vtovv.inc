subroutine da_transform_vtovv(grid, cv_size, be, cv, vv)

   !-----------------------------------------------------------------------
   ! Purpose: TBD
   !-----------------------------------------------------------------------

   implicit none

   type(domain),  intent(inout) :: grid
   integer,       intent(in)    :: cv_size ! Size of cv array.
   type(be_type), intent(in)    :: be   ! Background error structure.
   real,          intent(in)    :: cv(cv_size)   ! control variables.
   type(vp_type), intent(inout) :: vv   ! Grid point/EOF equivalent.

   integer :: s(4)   ! Index bounds into arrays.
   integer :: n      ! Loop counter.
   integer :: mz     ! Vertical truncations.
   integer :: ne     ! Ensemble size.

   logical :: scaling

   scaling = .false.

   if (trace_use) call da_trace_entry("da_transform_vtovv")

   if( use_rf )then
      !-------------------------------------------------------------------------
      ! [1.0] Fill vv arrays from 1-dimensional cv array.
      !-------------------------------------------------------------------------
#ifdef CLOUD_CV
      call da_cv_to_vv(cv_size, cv, (/ be%v1%mz, be%v2%mz, be%v3%mz, be%v4%mz, be%v5%mz,  be%v6%mz, be%v7%mz, be%v8%mz, be%v9%mz, be%v10%mz, be%v11%mz, be%alpha%mz, be%ne /), vv)
#else
      call da_cv_to_vv(cv_size, cv, (/ be%v1%mz, be%v2%mz, be%v3%mz, be%v4%mz, be%v5%mz, be%alpha%mz, be%ne /), vv)
#endif
   endif					! use wavelets:
   if( .not. use_rf .or. do_normalize ) s(1:2)=1

   !-------------------------------------------------------------------------
   ! [2.0] Perform VToVV Transform:
   !-------------------------------------------------------------------------

   ! [2.1] Transform 1st control variable:

   mz = be % v1 % mz
   s(3)=s(1)+mz-1
   if( use_rf .and. mz > 0 .and. len_scaling1(1) /= 0.0) then
      call da_transform_through_rf(grid, mz, be % v1 % rf_alpha, be % v1 % val, vv % v1)
   elseif( mz > 0 ) then
      s(4)=s(2)+nij(0,0,2)*nij(0,1,2)*mz-1
      call da_transform_through_wavelet(grid,mz,be%wsd(:,:,s(1):s(3)),cv(s(2):s(4)),vv%v1)
      s(2)=s(4)+1
   else
!      print'(a,": be%v1%mz=",I0)',__FILE__,mz
   endif
   if( do_normalize )call da_transform_rescale(mz,be%sd(:,:,s(1):s(3)),vv%v1)
   s(1)=s(3)+1

   ! [2.2] Transform 2nd control variable:

   mz = be % v2 % mz
   s(3)=s(1)+mz-1
   if( use_rf .and. mz > 0 .and. len_scaling2(1) /= 0.0) then
      call da_transform_through_rf(grid, mz, be % v2 % rf_alpha, be % v2 % val, vv % v2)
   elseif( mz > 0 ) then
      s(4)=s(2)+nij(0,0,2)*nij(0,1,2)*mz-1
      call da_transform_through_wavelet(grid,mz,be%wsd(:,:,s(1):s(3)),cv(s(2):s(4)),vv%v2)
      s(2)=s(4)+1
   else
!      print'(a,": be%v2%mz=",I0)',__FILE__,mz
   endif
   if( do_normalize )call da_transform_rescale(mz,be%sd(:,:,s(1):s(3)),vv%v2)
   s(1)=s(3)+1

   ! [2.3] Transform 3rd control variable

   mz = be % v3 % mz
   s(3)=s(1)+mz-1
   if( use_rf .and. mz > 0 .and. len_scaling3(1) /= 0.0) then
      call da_transform_through_rf(grid, mz, be % v3 % rf_alpha,be % v3 % val, vv % v3)
   elseif( mz > 0 ) then
      s(4)=s(2)+nij(0,0,2)*nij(0,1,2)*mz-1
      call da_transform_through_wavelet(grid,mz,be%wsd(:,:,s(1):s(3)),cv(s(2):s(4)),vv%v3)
      s(2)=s(4)+1
   else
!      print'(a,": be%v3%mz=",I0)',__FILE__,mz
   endif
   if( do_normalize )call da_transform_rescale(mz,be%sd(:,:,s(1):s(3)),vv%v3)
   s(1)=s(3)+1

   ! [2.4] Transform 4th control variable
      
   mz = be % v4 % mz
   s(3)=s(1)+mz-1
   if( use_rf .and. mz > 0 .and. len_scaling4(1) /= 0.0) then
      call da_transform_through_rf(grid, mz, be % v4 % rf_alpha, be % v4 % val, vv % v4)
   elseif( mz > 0 ) then
      s(4)=s(2)+nij(0,0,2)*nij(0,1,2)*mz-1
      call da_transform_through_wavelet(grid,mz,be%wsd(:,:,s(1):s(3)),cv(s(2):s(4)),vv%v4)
      s(2)=s(4)+1
   else
!      print'(a,": be%v4%mz=",I0)',__FILE__,mz
   endif
   if( do_normalize )call da_transform_rescale(mz,be%sd(:,:,s(1):s(3)),vv%v4)
   s(1)=s(3)+1

   ! [2.5] Transform 5th control variable

   mz = be % v5 % mz
   s(3)=s(1)+mz-1
   if( use_rf .and. mz > 0 .and. len_scaling5(1) /= 0.0) then
      call da_transform_through_rf(grid, mz, be % v5 % rf_alpha, be % v5 % val, vv % v5)
   elseif( mz > 0 ) then
      s(4)=s(2)+nij(0,0,2)*nij(0,1,2)*mz-1
      call da_transform_through_wavelet(grid,mz,be%wsd(:,:,s(1):s(3)),cv(s(2):s(4)),vv%v5)
      s(2)=s(4)+1
   else
!      print'(a,": be%v5%mz=",I0)',__FILE__,mz
   endif
   if( do_normalize )call da_transform_rescale(mz,be%sd(:,:,s(1):s(3)),vv%v5)
   s(1)=s(3)+1

#ifdef CLOUD_CV 
   ! [2.6] Transform 6th control variable

   if (cloud_cv_options == 3)then
      scaling = .true.
   else
      scaling = .false.
   endif

   mz = be % v6 % mz
   if( use_rf .and. mz > 0 .and. len_scaling6(1) /= 0.0) then
      if(cloud_cv_options == 1)then
         vv % v6 = 0.0
      elseif(cloud_cv_options == 2)then
         call da_transform_through_rf(grid, mz, be % v6 % rf_alpha, be % v6 % val, vv % v6)
      elseif(cloud_cv_options == 3)then
         call da_transform_through_rf(grid, mz, be % v6 % rf_alpha, be % v6 % val, vv % v6, scaling)
!        call da_transform_through_rf2(grid, mz, be % v6 % rf_alpha, be % v6 % val, vv % v6)
      endif
   elseif( .not. use_rf ) then
      call da_error(__FILE__,__LINE__,(/"no da_transform_through_wavelet for v6"/))
   endif

   ! [2.7] Transform 7th control variable

   mz = be % v7 % mz
   if( use_rf .and. mz > 0 .and. len_scaling7(1) /= 0.0) then
      if(cloud_cv_options == 1)then
         vv % v7 = 0.0
      elseif(cloud_cv_options == 2)then
         call da_transform_through_rf(grid, mz, be % v7 % rf_alpha, be % v7 % val, vv % v7)
      elseif(cloud_cv_options == 3)then
         call da_transform_through_rf(grid, mz, be % v7 % rf_alpha, be % v7 % val, vv % v7, scaling)
!        call da_transform_through_rf2(grid, mz, be % v7 % rf_alpha, be % v7 % val, vv % v7)
      endif
   elseif( .not. use_rf ) then
      call da_error(__FILE__,__LINE__,(/"no da_transform_through_wavelet for v7"/))
   endif

   ! [2.8] Transform 8th control variable

   mz = be % v8 % mz
   if( use_rf .and. mz > 0 .and. len_scaling8(1) /= 0.0) then
      if(cloud_cv_options == 1)then
         vv % v8 = 0.0
      elseif(cloud_cv_options == 2)then
         call da_transform_through_rf(grid, mz, be % v8 % rf_alpha, be % v8 % val, vv % v8)
      elseif(cloud_cv_options == 3)then
         call da_transform_through_rf(grid, mz, be % v8 % rf_alpha, be % v8 % val, vv % v8, scaling)
!        call da_transform_through_rf2(grid, mz, be % v8 % rf_alpha, be % v8 % val, vv % v8)
      endif
   elseif( .not. use_rf ) then
      call da_error(__FILE__,__LINE__,(/"no da_transform_through_wavelet for v8"/))
   endif

   ! [2.9] Transform 9th control variable

   mz = be % v9 % mz
   if( use_rf .and. mz > 0 .and. len_scaling9(1) /= 0.0) then
      if(cloud_cv_options == 1)then
         vv % v9 = 0.0
      elseif(cloud_cv_options == 2)then
         call da_transform_through_rf(grid, mz, be % v9 % rf_alpha, be % v9 % val, vv % v9)
      elseif(cloud_cv_options == 3)then
         call da_transform_through_rf(grid, mz, be % v9 % rf_alpha, be % v9 % val, vv % v9, scaling)
      endif
   elseif( .not. use_rf ) then
      call da_error(__FILE__,__LINE__,(/"no da_transform_through_wavelet for v9"/))
   endif

   ! [2.10] Transform 10th control variable

   mz = be % v10 % mz
   if( use_rf .and. mz > 0 .and. len_scaling10(1) /= 0.0) then
      if(cloud_cv_options == 1)then
         vv % v10 = 0.0
      elseif(cloud_cv_options == 2)then
         call da_transform_through_rf(grid, mz, be % v10 % rf_alpha, be % v10 % val, vv % v10)
      elseif(cloud_cv_options == 3)then
         call da_transform_through_rf(grid, mz, be % v10 % rf_alpha, be % v10 % val, vv % v10, scaling)
      endif
   elseif( .not. use_rf ) then
      call da_error(__FILE__,__LINE__,(/"no da_transform_through_wavelet for v10"/))
   endif

   ! [2.11] Transform 11th control variable

   mz = be % v11 % mz
   if( use_rf .and. mz > 0 .and. len_scaling11(1) /= 0.0) then
      if(cloud_cv_options == 1)then
         vv % v11 = 0.0
      elseif(cloud_cv_options == 2)then
         call da_transform_through_rf(grid, mz, be % v11 % rf_alpha, be % v11 % val, vv % v11)
      elseif(cloud_cv_options == 3)then
         call da_transform_through_rf(grid, mz, be % v11 % rf_alpha, be % v11 % val, vv % v11, scaling)
      endif
   elseif( .not. use_rf ) then
      call da_error(__FILE__,__LINE__,(/"no da_transform_through_wavelet for v11"/))
   endif

#endif

   ! [2.12] Transform alpha control variable

   ne = be % ne
   if (ne > 0) then
      mz = be % alpha % mz
      if( use_rf )then
         do n = 1, ne
            if ( anal_type_hybrid_dual_res ) then
               call da_transform_through_rf_dual_res(grid%intermediate_grid, mz, be % alpha % rf_alpha, & 
                             be % alpha % val, vv % alpha(:,:,:,n) )
            else
               call da_transform_through_rf(grid, mz, be % alpha % rf_alpha, be % alpha % val, vv % alpha(:,:,:,n) )
            endif
         end do
      else
         do n = 1, ne
            s(4)=s(2)+nij(0,0,2)*nij(0,1,2)*mz-1
            call da_transform_through_wavelet(grid,mz,be%alpha%wsd,cv(s(2):s(4)),vv%alpha(:,:,:,n))
            s(2)=s(4)+1
         end do
      endif
      if( do_normalize )then
         do n = 1, ne
            call da_transform_rescale(mz,be%alpha%sd,vv%alpha(:,:,:,n))
         end do
      endif
   endif

   if (trace_use) call da_trace_exit("da_transform_vtovv")

endsubroutine da_transform_vtovv
