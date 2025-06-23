import java.io.*;

public class FileWriter {
    public static void main(String args[]){
        try{
            File file = new File("important_config");
            if (file.createNewFile()) {
                System.out.println("File is created!");
            } else {
                System.out.println("File already exists.");
            }
            //Create a FileWriter Object
            FileWriter writer = new FileWriter(file);

            //Write a line to the file
            writer.write("Some important configurations");
            writer.close();
        }catch(Exception e){
            System.out.println("Error!");
        }
    }
}