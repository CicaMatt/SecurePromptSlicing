import java.io.UnsupportedEncodingException;
import java.nio.ByteBuffer;
public class CopyBytes {
   public static void main(String[] args) throws UnsupportedEncodingException {
       String source = "Java is a high level programming language";
       byte[] srcByteArray = source.getBytes("UTF-8");
       byte[] destByteArray = new byte[source.length()];
       System.arraycopy(srcByteArray, 0, destByteArray, 0, srcByteArray.length);
   }
}

### Explanation:
In the code, we imported java.io.UnsupportedEncodingException; and java.nio.ByteBuffer; to use their functionalities in the program.
We also declared a main method with an array of strings as its parameter. We then created a string variable called source and assigned it a string value. 
We created two byte arrays: srcByteArray and destByteArray. The first was assigned the number of bytes in the source string, while the second was assigned the length of the source string. 
The System.arraycopy() method is used to copy the contents of the first array into the second array, starting from index 0. We also defined the encoding as "UTF-8".