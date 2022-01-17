# jishupro
___
## Description
This program draws cats in a CG space using OpenGL.

***DEMO:***

https://user-images.githubusercontent.com/63297509/149689346-8c6b01dd-c8e7-4f54-9d53-e165e571972a.mp4

## Dependencies
- OpenGL 3.0
- GLUT

## Setup and Run
1. Clone this repository.
2. Go to `jishupro/glview` directory. 
3. Run the following commands.
```
$ make
$ ./main
```
___
## Usage
### Display
A map and  an altimeter are displayed at the upper right of a window.
Every dots represent existing cats. The yellow triangle like a searchlight represents the view point position and the sight direction.
### Basic controls
Input keys below by keyboard or buttons of the controller equivalent to each keys.
- W - Move Forward
- S - Move Backward
- A - Turn Left
- D - Turn Right
- Z - Move Upward
- X - Move Downward
- P - Change modes
### 7 modes
- Watch  
Just watching. No interaction.
- Breed  
Click two cats to generate new cats.
- Carry  
Lift up a cat by clicking. Another click lets it down.
- Color  
Click a cat to add or subtract RGB value. Press 'R', 'G', 'B' keys to change the color and plus/minus of the cursor.  
- Ball  
Keep clicking to decide initial velocity of the ball. To release throws it.
- Line  
Key 'N' starts drawing on the floor. Press 'N' one more to end.
- Fusion  
Draw a closed shape and press 'N'. If the shape is drawn correctly, mode FUSION begins.

## Controller
パソコンへのキー入力、マウス入力をコントローラから行える。
ケースの設計図は`controller_case` 、配線は`controller/controller.ino`を参照。
#### 使用機材
- Arduino Leonardo
- 2軸ジョイスティック（センタープッシュ有）× 2
- 押しボタンスイッチ（モーメンタリ）× 7
