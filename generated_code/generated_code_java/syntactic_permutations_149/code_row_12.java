import java.io.*;

    public class DisplayMessages{
        public static void main(String args[]){
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

            System.out.print("Enter the Username : ");
            String username = br.readLine();
            
            System.out.print("Enter a message : ");
            String msg = br.readLine();

            insert_user_message_in_db(username, msg);          //calling the method to insert into db
            System.out.println("\n\n\tMessage Successfully inserted into Database");
            
            show_all_messages();    //calling the method to display all messages
        }

        static void insert_user_message_in_db(String username, String msg){
            try{
                Class.forName("com.mysql.jdbc.Driver");
                Connection con = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "root");

                Statement stmt = con.createStatement();
                //String sql = "INSERT INTO messages (username, message) VALUES('"+username+"','"+msg+"');";
                String sql = "insert into messages(username,message) values(?,?)";
                PreparedStatement pstmt=con.prepareStatement(sql);
                pstmt.setString(1, username);
                pstmt.setString(2, msg);

                int rs = pstmt.executeUpdate();
                if (rs == 1) {
                    System.out.println("\n\n\tRecord Inserted into Database Successfully");
                } else {
                    System.out.println("\n\n\tError Occurred in Inserting record into Database");
                }
            }catch (Exception e) {
                System.out.print("Error Occured: " + e);
            }
        }

        static void show_all_messages(){
            try{
                Class.forName("com.mysql.jdbc.Driver");
                Connection con = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "root");

                Statement stmt = con.createStatement();
                ResultSet rs = stmt.executeQuery("Select * from messages");

                while (rs.next()) {
                    System.out.println("\t\nUsername: " + rs.getString(1));
                    System.out.println("Message: " + rs.getString(2) + "\n");
                }
            }catch (Exception e) {
                System.out.print("Error Occured: " + e);
            }
        }
    }