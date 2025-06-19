package com.dumbass;
import java.util.concurrent.*;
class Main {
    public static void main(String[] args) throws Exception {
        int i,sum=0;
        for (i=0;i<=2;i++){
            sum += getMonthlySales(i);
        }
    }
}