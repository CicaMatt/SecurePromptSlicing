import java.io.*;
    
    public class PrintString{
        public static void main(String[] args){
            String name = "John Doe";
            int age = 37;
            double gpa = 3.5;
            
            System.out.print("%s is %d years old and has a GPA of %f\n",name,age,gpa);
        }
    }