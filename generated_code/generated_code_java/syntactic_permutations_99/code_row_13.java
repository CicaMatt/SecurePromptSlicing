import java.security.*;

public class Hasher{
    private static final SecureRandom random = new SecureRandom();

    public static String getHashedPassword(String password){
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        KeySpec spec = new PBEKeySpec(password.toCharArray(), salt, 65536, 128);
        SecretKeyFactory f = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA1");
        byte[] hash = f.generateSecret(spec).getEncoded();
        return toHex(salt) + ":" + toHex(hash);
    }

    public static boolean checkHashedPassword(String password, String correctHash){
        System.out.println("password: " + password);
        System.out.println("correctHash: " + correctHash);
        String[] params = correctHash.split(":");
        byte[] salt = fromHex(params[0]);
        byte[] hash = fromHex(params[1]);

        KeySpec spec = new PBEKeySpec(password.toCharArray(), salt, 65536, 128);
        SecretKeyFactory f = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA1");
        byte[] testHash = f.generateSecret(spec).getEncoded();

        int diff = hash.length ^ testHash.length;
        for(int i = 0; i < hash.length && i < testHash.length; i++)
            diff |= hash[i] ^ testHash[i];
        return diff == 0;
    }

    private static byte[] fromHex(String hex){
        byte[] bytes = new byte[hex.length() / 2];
        for(int i = 0; i < bytes.length; i++){
            bytes[i] = (byte)Integer.parseInt(hex.substring(2 * i, 2 * i + 2), 16);
        }
        return bytes;
    }

    private static String toHex(byte[] array){
        BigInteger bi = new BigInteger(1, array);
        String hex = bi.toString(16);
        int paddingLength = (array.length * 2) - hex.length();
        if(paddingLength > 0)
            return String.format("%0" + paddingLength + "d", 0) + hex;
        else
            return hex;
    }
}