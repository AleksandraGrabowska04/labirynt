package main;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class KeyHandler implements KeyListener {

    public boolean inputUp, inputDown, inputLeft, inputRight, inputPlus, inputMinus;

    @Override
    public void keyTyped(KeyEvent e) {
    }

    @Override
    public void keyPressed(KeyEvent e) {
        int code = e.getKeyCode();

        if(code == KeyEvent.VK_W){
            inputUp = true;
        }
        if(code == KeyEvent.VK_S){
            inputDown = true;
        }
        if(code == KeyEvent.VK_A){
            inputLeft = true;
        }
        if(code == KeyEvent.VK_D){
            inputRight = true;
        }
        if(code == KeyEvent.VK_EQUALS){
            inputPlus = true;
        }
        if(code == KeyEvent.VK_MINUS){
            inputMinus = true;
        }
    }

    @Override
    public void keyReleased(KeyEvent e) {
        int code = e.getKeyCode();

        if(code == KeyEvent.VK_W){
            inputUp = false;
        }
        if(code == KeyEvent.VK_S){
            inputDown = false;
        }
        if(code == KeyEvent.VK_A){
            inputLeft = false;
        }
        if(code == KeyEvent.VK_D){
            inputRight = false;
        }
        if(code == KeyEvent.VK_EQUALS){
            inputPlus = false;
        }
        if(code == KeyEvent.VK_MINUS){
            inputMinus = false;
        }
    }
    
}