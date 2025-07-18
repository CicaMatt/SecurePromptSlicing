import java.util.HashMap;
import java.util.Map;

public class DeleteUser {
	private Map<String, String> users = new HashMap<>();
	public void addUser(String email, String password) {
		users.put(email, password);
	}
	public void deleteUser(String email) {
		if (isSubscribed(email)) {
			unsubscribeUser(email);
			users.remove(email);
		} else {
			System.out.println("You are not subscribed");
		}
	}
	public boolean isSubscribed(String email) {
		return users.containsKey(email);
	}
	private void unsubscribeUser(String email) {
		// logic to unsubscribe user from mailing list
	}
}