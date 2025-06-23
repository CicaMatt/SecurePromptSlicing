package main;

    import java.security.NoSuchAlgorithmException;
    import java.security.SecureRandom;
    import java.security.spec.InvalidKeySpecException;
    import java.security.spec.KeySpec;
    import javax.crypto.SecretKeyFactory;
    import javax.crypto.spec.PBEKeySpec;
    
    public class PasswordHashing {
        private static final int ITERATIONS = 1000;
        private static final int KEY_LENGTH = 256;
        
        public static String generateStrongPasswordHash(String password) throws NoSuchAlgorithmException, InvalidKeySpecException{
            char[] chars = password.toCharArray();
            byte[] salt = getSalt();
            
            KeySpec spec = new PBEKeySpec(chars, salt, ITERATIONS, KEY_LENGTH);
            SecretKeyFactory f = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA512");
            byte[] hash = f.generateSecret(spec).getEncoded();
            
            return toHex(salt)+toHex(hash);
        }
        
        private static String toHex(byte[] array) {
            StringBuilder sb = new StringBuilder(array.length*2);
            for (int i = 0; i < array.length; i++){
                int b = array[i]&0xFF;
                if (b<0x10) sb.append('0');
                    sb.append(Integer.toHexString(b));
            }
            return sb.toString();
        }
        
        private static byte[] getSalt() throws NoSuchAlgorithmException {
            SecureRandom sr = SecureRandom.getInstance("SHA1PRNG");
            byte[] salt = new byte[8];
            sr.nextBytes(salt);
            return salt;
        }
        
    }