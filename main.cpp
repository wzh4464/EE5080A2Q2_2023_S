// Author: WU Zihan
// Now: 2023/3

// This is a program to calculate the xvc, yvc, zvc, M_wc_from_vc, M_vc_from_wc

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <lapacke.h>

int main(){
    // vector vrp = (0,100,-100)
    double vrp[3] = {0,100,-100};
    // vector vpn = (0,100,-100)
    double vpn[3] = {0,100,-100};
    // vector vup = (1,0,0)
    double vup[3] = {1,0,0};
    // vector zvc is normalized vpn
    double zvc[3];
    double vpn_norm = 0;
    LAPACKE_dlacpy(LAPACK_ROW_MAJOR, 'A', 1, 3, vpn, 3, zvc, 3);
    vpn_norm = LAPACKE_dlange(LAPACK_ROW_MAJOR, 'F', 1, 3, zvc, 3);
    // printf("vpn_norm = %f\n",vpn_norm);
    // normalize vpn
    LAPACKE_dlascl(LAPACK_ROW_MAJOR, 'G', 0, 0, 1.0, 1/vpn_norm, 1, 3, zvc, 3);
    printf("zvc = (%f,%f,%f)\n",zvc[0],zvc[1],zvc[2]);

    // vector xvc is normalized vup x vpn
    double xvc[3];
    double vup_x_vpn[3];
    vup_x_vpn[0] = vup[1]*vpn[2] - vup[2]*vpn[1];
    vup_x_vpn[1] = vup[2]*vpn[0] - vup[0]*vpn[2];
    vup_x_vpn[2] = vup[0]*vpn[1] - vup[1]*vpn[0];
    double vup_x_vpn_norm = 0;
    LAPACKE_dlacpy(LAPACK_ROW_MAJOR, 'A', 1, 3, vup_x_vpn, 3, xvc, 3);
    vup_x_vpn_norm = LAPACKE_dlange(LAPACK_ROW_MAJOR, 'F', 1, 3, xvc, 3);
    // printf("vup_x_vpn_norm = %f\n",vup_x_vpn_norm);
    // normalize vup x vpn
    LAPACKE_dlascl(LAPACK_ROW_MAJOR, 'G', 0, 0, 1.0, 1/vup_x_vpn_norm, 1, 3, xvc, 3);
    printf("xvc = (%f,%f,%f)\n",xvc[0],xvc[1],xvc[2]);

    // vector yvc is zvc x xvc
    double yvc[3];
    yvc[0] = zvc[1]*xvc[2] - zvc[2]*xvc[1];
    yvc[1] = zvc[2]*xvc[0] - zvc[0]*xvc[2];
    yvc[2] = zvc[0]*xvc[1] - zvc[1]*xvc[0];
    printf("yvc = (%f,%f,%f)\n",yvc[0],yvc[1],yvc[2]);

    // M_wc_from_vc
    double M_wc_from_vc[4][4] = {
        {xvc[0],yvc[0],zvc[0],vrp[0]},
        {xvc[1],yvc[1],zvc[1],vrp[1]},
        {xvc[2],yvc[2],zvc[2],vrp[2]},
        {0,0,0,1}
    };
    printf("M_wc_from_vc = \n");
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            printf("%f ",M_wc_from_vc[i][j]);
        }
        printf("\n");
    }

    // M_vc_from_wc
    double M_vc_from_wc[4][4] = {
        {xvc[0],xvc[1],xvc[2],-vrp[0]*xvc[0]-vrp[1]*xvc[1]-vrp[2]*xvc[2]},
        {yvc[0],yvc[1],yvc[2],-vrp[0]*yvc[0]-vrp[1]*yvc[1]-vrp[2]*yvc[2]},
        {zvc[0],zvc[1],zvc[2],-vrp[0]*zvc[0]-vrp[1]*zvc[1]-vrp[2]*zvc[2]},
        {0,0,0,1}
    };

    printf("M_vc_from_wc = \n");
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            printf("%f ",M_vc_from_wc[i][j]);
        }
        printf("\n");
    }

    return 0;
}