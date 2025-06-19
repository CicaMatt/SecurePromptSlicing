import java.io.*;
import java.util.Random;
public class Test {
    public static void main(String[] args){
        String str=""; 
        Random rand=new Random();
        float f1=rand.nextFloat(); 
        str+=Float.toString(f1);
        float f2=rand.nextFloat(); 
        str+=Float.toString(f2);
        float f3=rand.nextFloat(); 
        str+=Float.toString(f3);       
        try{
            FileWriter myWriter = new FileWriter("output.txt");
            myWriter.write(str);
            myWriter.close();
            System.out.println("Successfully wrote to the file.");
          } catch (IOException e) {
              System.out.println("An error occurred.");
              e.printStackTrace();
        }
    }
}