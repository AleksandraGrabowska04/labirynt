package main;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;

import javax.swing.JPanel;

import path.PathManager;
import tile.TileManager;

public class LabyrinthPanel extends JPanel implements Runnable{

    KeyHandler keyH = new KeyHandler();
    Thread labThread;
    TileManager tileMng = new TileManager(this);
    PathManager pathMng = new PathManager(this, tileMng);
    UserInterface userInter = new UserInterface(this, tileMng, pathMng);

    final public int originalTileSize = 16;
    final int FPS = 30;
    final public int gridLimitX = 1000;
    final public int gridLimitY = 1000;
    final public int pathLimit = 1000000;

    public int screenWidth = 800;
    public int screenHeight = 800;
    int viewSpeed = 1;

    public int viewX = 0;
    public int viewY = 0;
    
    public int tileSize = originalTileSize;

    public LabyrinthPanel () {
        this.setPreferredSize(new Dimension(screenWidth, screenHeight));
        this.setBackground(Color.white);
        this.setDoubleBuffered(true);
        this.addKeyListener(keyH);
        this.setFocusable(true);
    }

    public void startLabThread() {
        labThread = new Thread(this);
        labThread.start();
    }

    @Override
    public void run() {

        double timeInterval = 1000000000/FPS;
        double timeNextDraw = System.nanoTime() + timeInterval;

        while(labThread != null){
            update();
            repaint();

            try {
                double timeRemaining = (timeNextDraw - System.nanoTime())/1000000;
                
                if(timeRemaining < 0){
                    timeRemaining = 0;
                }
                
                Thread.sleep((long) timeRemaining);
                
                timeNextDraw += timeInterval;
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public void update() {
        if(keyH.inputDown == true){
            viewY += viewSpeed;
        }
        if(keyH.inputUp == true){
            viewY -= viewSpeed;
        }
        if(keyH.inputRight == true){
            viewX += viewSpeed;
        }
        if(keyH.inputLeft == true){
            viewX -= viewSpeed;
        }
        if(keyH.inputPlus == true){
            tileSize += 1;
        }
        if(keyH.inputMinus == true && tileSize > 1){
            tileSize -= 1;
        }
        pathMng.update(keyH);
    }

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);

        Graphics2D g2 = (Graphics2D) g;

        tileMng.draw(g2);
        pathMng.draw(g2);
        userInter.draw(g2);
    }
}