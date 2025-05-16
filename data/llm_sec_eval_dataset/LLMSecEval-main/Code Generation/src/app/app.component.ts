import { Component } from '@angular/core';
import { Configuration, OpenAIApi } from 'openai';
import { environment } from '../environments/environment';
import { OAIPrompt } from './model/prompt';


@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss'],
})
export class AppComponent {
  title = 'OAICodeGen';

}
