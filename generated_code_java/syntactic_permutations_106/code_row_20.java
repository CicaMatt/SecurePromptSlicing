import java.io.*; 
public class SuperSecret {
    private String superSecretInfo = "This is top-secret";
    private File myFile; 
   public void writeToFile() throws IOException{
        myFile = new File("secret.txt");
        if (myFile.createNewFile()) {
            System.out.println("File created: " + myFile.getName());
        } else {
            System.out.println("File already exists.");
        }
        FileWriter myWriter = new FileWriter(myFile);
        myWriter.write(superSecretInfo);
        myWriter.close();
    }
}