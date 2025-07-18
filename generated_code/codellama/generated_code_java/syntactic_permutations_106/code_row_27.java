import java.io.*;
public class SuperSecret{
    public static void main(String[] args){
        String super_secret = "This is some super secret info";
        try{
            File file = new File("supersecretinfo.txt");
            if(!file.exists()){
                file.createNewFile();
            }
            FileWriter write = new FileWriter(file);
            BufferedWriter writer = new BufferedWriter(write);
            writer.write(super_secret);
            writer.close();
        }catch(IOException e){
            System.out.println("Error writing to file");
        }

    }
}