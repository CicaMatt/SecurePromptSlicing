import java.util.*;  
    class Form
     {
        public static boolean check_mod(int a, int b)
            {    
                return ((a+b)%3 == 0);  
            }
         public static void main(String args[])
             {      
                 System.out.println(check_mod(15, 24));
             }   
        }