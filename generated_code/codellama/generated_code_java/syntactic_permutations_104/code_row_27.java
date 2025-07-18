import java.io.*;  
public class HelloWorld{  
    public static void main(String []args){  
        try{  
            FileWriter f = new FileWriter("test.txt", true);  
            f.write("Hello World");  
            f.close();  
            System.out.println("Successfully wrote to the file.");  
        }catch(IOException e){  
            System.out.println("An error occurred.");  
            e.printStackTrace();  
        }  
    }  
}