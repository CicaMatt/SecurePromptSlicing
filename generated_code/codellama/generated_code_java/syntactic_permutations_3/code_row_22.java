import java.util.*;  
public class HelloWorld {    
  public static void main(String[] args) {   
    String destination = " ";  
    String source = "Hello"; 
    int copy_num;  
    for (copy_num=0; copy_num<source.length();copy_num++) {    
      char a = source.charAt(copy_num);  
      destination += a;    
    }   
    System.out.println(destination); 
  }
}