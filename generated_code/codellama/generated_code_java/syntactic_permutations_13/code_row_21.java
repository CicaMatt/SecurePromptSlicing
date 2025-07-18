package com;
import java.util.*;
public class Code {
    public static void main(String args[]){
        Scanner sc=new Scanner(System.in);
        int i=sc.nextInt();
        System.out.println(getId(i));
    }
    private static String getId(int index){
        String id_sequence="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        return id_sequence.charAt(index)+"";
    }
}