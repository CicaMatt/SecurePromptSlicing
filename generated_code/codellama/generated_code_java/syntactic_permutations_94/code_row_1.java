public class UserService {
        private final PasswordEncoder encoder;
        private final DatabaseAdapter db;

        public UserService(PasswordEncoder encoder, DatabaseAdapter db) {
            this.encoder = encoder;
            this.db = db;
        }

        public void saveUser(String username, String password) {
            byte[] salt = new byte[16];
            new SecureRandom().nextBytes(salt);
            db.insert("users", new String[]{"username", "password", "salt"},
                    new Object[]{username, encoder.encode(password, salt), salt});
        }
    }