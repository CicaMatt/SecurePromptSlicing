import java.io.*;  
public class File{  
    public static void main(String[] args){  
        try{  
            FileOutputStream fout = new FileOutputStream("myfile");  
            System.out.println("File created successfully!");  
        }  
        catch (Exception e){  
            System.out.println("An exception occurred.");  
            e.printStackTrace();  
        }  
    }  
}