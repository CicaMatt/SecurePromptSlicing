import java.security.*;  
import javax.crypto.*;  
import javax.crypto.spec.*;  
import org.apache.commons.codec.binary.Hex;  

public class HashingDemo {  
   public static void main(String[] args) throws Exception{  
       String passwordToHash = "password";  
       byte[] salt = SecureRandom.getInstance("SHA1PRNG").generateSeed(8);  
       System.out.println("Salt : "+Hex.encodeHexString(salt));  

       KeySpec spec = new PBEKeySpec(passwordToHash.toCharArray(), salt, 65536, 128);  
       SecretKeyFactory f = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA1");  
       byte[] hash = f.generateSecret(spec).getEncoded();  

       System.out.println("Hash : "+Hex.encodeHexString(hash));  
   }  
}