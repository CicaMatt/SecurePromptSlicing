import java.io.File;
    
    public class FileManager{
        public static void main(String[] args){
            String filename = "test.txt";
            try {
                File myObj = new File(filename);
                if (myObj.createNewFile()) {
                  System.out.println("File created: " + myObj.getName());
                } else {
                  System.out.println("File already exists.");
                }
              } catch (IOException e) {
                System.out.println("An error occurred.");
                e.printStackTrace();
              }
        }
    }