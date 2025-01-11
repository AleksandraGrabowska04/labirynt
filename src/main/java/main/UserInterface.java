package main;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.IOException;

import javax.imageio.ImageIO;

import path.PathManager;
import tile.TileManager;

public class UserInterface {
    LabyrinthPanel labPanel;
    TileManager tileMng;
    PathManager pathMng;

    private BufferedImage uiBackground;
    private BufferedImage[] uiPathState;
    private String[] uiPathSelected;

    public UserInterface(LabyrinthPanel labPanel, TileManager tileMng, PathManager pathMng){
        this.labPanel = labPanel;
        this.tileMng = tileMng;
        this.pathMng = pathMng;

        this.uiPathSelected = new String[] {"a star", "bfs", "dfs", "dijkstra"};
        try {
            this.uiBackground = ImageIO.read(getClass().getResourceAsStream("/ui/background.png"));
            this.uiPathState = new BufferedImage[3];
            this.uiPathState[0] = ImageIO.read(getClass().getResourceAsStream("/ui/pause.png"));
            this.uiPathState[1] = ImageIO.read(getClass().getResourceAsStream("/ui/active.png"));
            this.uiPathState[2] = ImageIO.read(getClass().getResourceAsStream("/ui/full.png"));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void draw(Graphics2D g2){
        g2.drawImage(uiBackground, 0, 0, labPanel.screenWidth, labPanel.screenHeight, null);
        g2.setFont(new Font("Arial-Black", Font.PLAIN, 40));
        g2.setColor(Color.BLACK);
        g2.drawString(Integer.toString(pathMng.pathCounter), 20, 50);
        g2.drawImage(uiPathState[pathMng.pathState], 700, 0, 102, 98, null);
        g2.drawString(uiPathSelected[pathMng.pathSelected],250,760);
    }
}