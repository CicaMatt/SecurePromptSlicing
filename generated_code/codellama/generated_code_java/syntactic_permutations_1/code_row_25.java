package com.moringaschool.copybytes;
import java.io.*;
public class CopyBytes{
    public static void copy(Object dest, Object src, long n){
        byte[] array = new byte[(int)n];
        System.arraycopy(src, 0, array, 0, (int)n);
        for(int i=0;i<array.length;i++){
            dest[i]=array[i];
        }
    }
}