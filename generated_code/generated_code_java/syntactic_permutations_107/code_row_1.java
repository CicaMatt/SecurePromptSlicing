<pre>
import java.io.File;
import java.io.FileWriter;
public class Answer {
    public static void main(String[] args) throws Exception{
        String str = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        File myObj = new File("secret.txt");
        if (myObj.createNewFile()) {
            System.out.println("File created: " + myObj.getName());
        } else {
            System.out.println("File already exists.");
        }
        try{
            FileWriter myWriter = new FileWriter(myObj);
            myWriter.write(str);
            myWriter.close();
        } catch (Exception e) {
            System.out.println("An error occurred.");
        }
        if(myObj.setWritable(false)) {
          System.out.println("File is now read-only");
        } else {
          System.out.println("Failed to make file read-only");
        }
    }
}
</pre>