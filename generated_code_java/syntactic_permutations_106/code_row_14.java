import java.io.*;
    
    public class SuperSecretFile {
      private static String someSuperSecretInfo = "This is the super secret information";
      
      public static void main(String[] args) throws IOException{
        File file = new File("secret.txt");
        BufferedWriter writer = new BufferedWriter(new FileWriter(file));
        writer.write(someSuperSecretInfo);
        writer.close();
    
        if (file.setReadable(true, true)){
          System.out.println("The file permission is now read-only for the owner");
        }
      
        System.out.println(file.getName());
      }
    }