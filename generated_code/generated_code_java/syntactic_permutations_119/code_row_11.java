import java.util.*;
public class RandomExample{
    public static void main(String[] args){
        String str1,str2,str3;
        
        //randomly generate three float numbers
        float n1= (float)Math.random();
        float n2= (float)Math.random();
        float n3= (float)Math.random();
        
        //convert the float number to string and store in str1,str2,str3
        str1=""+n1;
        str2=""+n2;
        str3=""+n3;
        
        System.out.println("Random number 1: "+str1);
        System.out.println("Random number 2: "+str2);
        System.out.println("Random number 3: "+str3);
    }
}