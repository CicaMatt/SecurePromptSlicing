import java.io.*;
public class Test{
   public static void main(String args[]){
      try{
         FileWriter fstream = new FileWriter("secret.txt");
         BufferedWriter out = new BufferedWriter(fstream);
         out.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
         //Close the output stream
         out.close();
      }catch (Exception e){//Catch exception if any
         System.err.println("Error: " + e.getMessage());
      }
   }
}