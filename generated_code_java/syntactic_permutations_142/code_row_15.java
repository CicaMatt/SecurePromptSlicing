public class Unsubscribe {
        private String emailAddress;
        private Database database;

        public Unsubscribe(String emailAddress, Database database) {
            this.emailAddress = emailAddress;
            this.database = database;
        }

        public void unsubscribe() throws Exception {
            if (database.isEmailInDatabase(emailAddress)) {
                database.removeFromDatabase(emailAddress);
                System.out.println("You have been removed from the database.");
            } else {
                throw new Exception("You are not in the database.");
            }
        }
    }

    public class Database {
        private List<String> emailList;

        public Database(List<String> emailList) {
            this.emailList = emailList;
        }

        public boolean isEmailInDatabase(String emailAddress) {
            return emailList.contains(emailAddress);
        }

        public void removeFromDatabase(String emailAddress) {
            emailList.remove(emailAddress);
        }
    }