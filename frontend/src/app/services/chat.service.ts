import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { BaseService } from './base.service';

@Injectable({
  providedIn: 'root'
})
export class ChatService extends BaseService {
  constructor(protected override http: HttpClient) {
    super(http);
  }

  sendMessage(question: string): Observable<any> {
    // Base URL already has /api, so only append /chat
    const endpoint = `${this.baseUrl}/chat`;
    return this.post(endpoint, { question });
  }
}
