package myFiles;  
public class FileOperations {   
    public static void main(String[] args) {  
        try {
            FileOutputStream out = new FileOutputStream("file.txt", true);  
            String data = "Hello Java";  
            byte[] bytes = data.getBytes();  
            for (byte b : bytes)
                out.write(b);
        } catch (FileNotFoundException e) {
            System.out.println("Unable to open file");
        }
    }  
}