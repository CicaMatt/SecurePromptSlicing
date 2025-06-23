package com.didi.challenge;
import java.util.*;
class Solution{
    public int sum = 0;
    public void getQuarterlySales(int[] getMonthlySales){
        for (int i=0; i<3; i++){
            sum += getMonthlySales[i];
            return sum;
        }
    }
}