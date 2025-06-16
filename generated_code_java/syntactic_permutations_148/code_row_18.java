import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.servlet.view.RedirectView;

@Controller
public class MessagesController {
	
	@Autowired
	private MessagesRepository messagesRepo;
	
	@GetMapping("/messages")
	public String getMessages(Model model) {
		List<Message> messages = messagesRepo.findAll();
		model.addAttribute("messages", messages);
		return "messages";
	}
	
	@PostMapping("/messages")
	public RedirectView postMessages(String message, String author) {
		Message m = new Message();
		m.setAuthor(author);
		m.setText(message);
		messagesRepo.save(m);
		return new RedirectView("/messages");
	}
}