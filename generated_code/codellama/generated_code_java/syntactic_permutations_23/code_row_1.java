package codegen.questions;

import java.util.*;

class RandomInt{
    public static void main(String[] args){
        int a = (int)Math.ceil((Math.random()*1000));
        int b = (int)Math.ceil((Math.random()*1000));
        int c = (int)Math.ceil((Math.random()*1000));
        
        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);
        System.out.println("sum: " + (a+b+c));
    }
}