// title:  game title
// author: game developer
// desc:   short description
// script: js

var t=0
var x=96
var y=24

const sprites = [
  // x, y, w, h, eye_pos
  {x: 115, y: 40, w: 10, h: 40, eyex: 8},
  {x: 0,   y: 0,  w: 13, h: 40, eyex: 11},
  {x: 15,  y: 0,  w: 16, h: 40, eyex: 14},
  {x: 33,  y: 0,  w: 18, h: 40, eyex: 16},
  {x: 53,  y: 0,  w: 24, h: 40, eyex: 22},
  {x: 79,  y: 0,  w: 23, h: 40, eyex: 21},
  {x: 104, y: 0,  w: 23, h: 40, eyex: 21},
  {x: 0,   y: 40, w: 31, h: 40, eyex: 26},
  {x: 33,  y: 40, w: 31, h: 40, eyex: 29},
  {x: 66,  y: 40, w: 23, h: 40, eyex: 21},
  {x: 91,  y: 40, w: 24, h: 40, eyex: 22},
  {x: 0,   y: 80, w: 29, h: 40, eyex: 27},
  {x: 31,  y: 80, w: 31, h: 40, eyex: 29},
  {x: 64,  y: 80, w: 21, h: 40, eyex: 19},
  {x: 87,  y: 80, w: 23, h: 40, eyex: 21},
]

function printSprite(idx, xpos, ypos, flip) {
  const x = sprites[idx].x
  const y = sprites[idx].y
  const w = sprites[idx].w
  const h = sprites[idx].h
  const eyex = sprites[idx].eyex
  const sx = Math.floor(x/8)
  const offsX = x - sx*8
  const sw = Math.ceil((x + w)/8) - sx
  const sy = Math.floor(y/8)
  const offsY = y - sy*8
  const sh = Math.ceil((y + h)/8) - sy
  clip(xpos - eyex, ypos, w, h);
  const sprIdx = sy*16 + sx
  spr(sprIdx, xpos - offsX - eyex, ypos - offsY,
      0, 1, flip, 0, sw, sh)
  clip()
  //rectb(xpos-1, ypos-1, w+2, h+2, 15)
}

var spriteIdx = 0
var spriteSpeed = 0.15
var flip = 0

function nextSprite() {
  spriteIdx += spriteSpeed
  if (spriteIdx >= sprites.length) {
    spriteIdx = 7
  }
}

function TIC()
{
  // if(btn(0))y--
  // if(btn(1))y++

  if(btn(2)) {
    flip = 1
    x--
    nextSprite()
  } else if(btn(3)) {
    flip = 0
    x++
    nextSprite()
  } else {
    spriteIdx = 0
  }
  const spriteIdxInt = Math.floor(spriteIdx)

  cls(0)
  printSprite(spriteIdxInt, x, y, flip)
  print(spriteIdx.toString())
}

// <TILES>
// 000:00000066000006660000066600000666000006690000066600000006000009f9
// 001:6666000066666000669900009996000099996000699900006699000099000000
// 002:0000000000000006000000060000000600000006000000060000000000000009
// 003:66666600666666606666990066999600699999606669990006669900f9990000
// 005:000066660006666600066666000666990006699900066669000006660009f999
// 006:6600000066600000990000009600000099600000990000009900000000000000
// 008:0000000000000066000006660000066600000666000006690000066600000006
// 009:0000000066660000666660006699000099960000999960006999000066990000
// 011:0000000000000000000000060000006600000066000000660000006600000066
// 012:0000000000000000666660006666660066699000699960009999960066999000
// 014:0000000000000000000000060000000600000006000000060000000600000000
// 015:0000000066666600666666606666990066999600699999606669990006669900
// 016:000009ff00009999000999990009999900099999000999990009999900099999
// 017:f9000000ff000000ff000000ff000000fff00000fff00000fff00000fff00000
// 018:0000000900000099000000990000099900000999000099990000999900009999
// 019:fff9000099ff900099fff00099fff00099fff0009ffff0009fff9000ffff0000
// 020:0000000000000000000000000000000000000000000000090000000f0000009f
// 021:0009fff9009f999f0999999f0999999f999999ff99999fff9999ffff99999fff
// 022:0000000090000000f0000000f0000000f0000000900000000000000000000000
// 023:0000000000000000000000000000000000000000000000000000000000000009
// 024:000009f900009fff0009f999009f999909f999990f9999999f99999ff99999ff
// 025:99000000f9000000ff000000ff000000ff000000ff000000f9000000f0000000
// 027:000000000000009f0000009f0000099900009999000999990099999f09999fff
// 028:6669900099900000ff9000009ff000009ff000009ff00000fff00000ff900000
// 029:0000000000000000000000000000000000000000000000000000000000000009
// 030:00000009000009990000999900099999009999990999999f99999fff999fffff
// 031:f9990000fff90000ffff0000ffff0000ffff0000ffff0000fff99990fff99990
// 032:0009999f000f999f009f9999009f999900fff99909ffff9909fffff90fffffff
// 033:fff00000fff00000fff000009f00000099000000999000009999000099990000
// 034:000999990009ff99009fffff009fffff09ffffff09ffffff0fffffff0fffffff
// 035:99ff00009999000099999000ff999990fff09990fff00000fff9000099ff9000
// 036:000000ff000009ff00000fff00000fff00009fff00009fff00009fff0000ffff
// 037:f9999999ff999999ffff9999fffff900ffffff00ffffff90fffffff0fff9fff9
// 038:0000000000000000999000009990000000000000000000000000000000000000
// 039:000000090000009f000000ff000000ff000009ff000009ff00000fff00000fff
// 040:f9999ffff99999ffff999990fff99999fffff999ffffff99fffffff9ffffffff
// 041:9000000000000000000000000000000090000000000000000000000000000000
// 042:00000000000000000000000f0000000f0000009f000000ff000000ff000000ff
// 043:9999ffff999fffff999fffff999fffff99fffff999ffff9999fff966999ff900
// 044:ff000000f9000000f00000009000000000000000990000009999000009990000
// 045:0000000900000009000000090000000900000009000000090000000000000000
// 046:999fffff99ffffff99ffffff99ffffff99ffffff99fffff999ffffffffffffff
// 047:ff966990ff000000f9000000f0000000900000000000000090000000f0000000
// 048:0fffffff09ffffff09ffffff00ffffff00ffffff09ffffff0fffffff9fffffff
// 049:ff000000ff000000ff900000ff900000fff00000fff00000ff000000f0000009
// 050:0fffffff09ffffff00ffffff00ffffff00ffffff09ffffff0ffffff9ffffff9f
// 051:9ffff9009fffff00ffffff90fffffff0fffffff0ffffff90fffff900ffff9000
// 052:0000ffff0000ffff0000ffff0000ffff0009ffff009fffff00ffffff09ffffff
// 053:ff99ffffff9fffffff0ffffff90ffffff009fffff000ffff9099ffff09ffffff
// 054:0000000090000000f0000000f9000000ff000000ff000000ff000000f9000000
// 055:00000fff00009fff00009fff00009fff0000ffff0000ffff00099fff009fffff
// 056:fffffffffff9ffffff99ffffff09ffffff009fffff0009fff9000ffff009ffff
// 057:90000000f0000000f9000000ff000000ff900000fff00000fff00000ff900000
// 058:0000009f0000009f000000090000000900000000000000000000000000000099
// 059:999fff00ffffff00ffffff90fffffff09ffffff999ffffff099fffff99fffff9
// 061:000000000000000000000000000000000000000000000009000000090000000f
// 062:ffffffffff99fffffff99ffffff999ffffff999fffff999fffff99fffff9ffff
// 063:f9000000ff900000fff90000ffff9000fffff000fffff000ffff9000fff90000
// 064:ffffff9ffffff9909fff90006660000069600000699600009999900099999990
// 065:0000000f0000000f000000090000000000000000000000000000000000000000
// 066:ffffff0ffffff90ffff999966660099969900099699000999999000099999900
// 067:ff900000f9000000600000000000000000000000900000009900000000000000
// 068:0ffffff90ffffff009ffff90006ff00009660000099600000999900000999990
// 069:09ffffff00ffff90006f90009966000099960000099990000009999000000000
// 070:9000000000000000000000000000000000000006000000990000099900000099
// 071:09ffffff9ffffff99fffff9069ff900066000009600000999000000099900000
// 072:909fffff009fffff069ffff96660ff9099600000999000000999900000000000
// 073:f900000090000000000000090000000000000000000000000000000000000000
// 074:000099999966999f996669ff996000ff9900006f990099900900999000000999
// 075:ffffff90fffff900ffff9000fff90000f9000000000000000000000090000000
// 077:000009ff0000fff900006f990096600909966000999900000999000000099000
// 078:f99fffff9996ffff9966ff909960000099600000099000000099000000000000
// 079:ff90000090000000000000000000000000000000000000000000000000000000
// 082:0000000000000666000066660000666600006669000066990000666600000066
// 083:0000000066600000666600006990000099600000999600009990000069900000
// 087:066666606666666666666990666999606699999666669990006669909f999000
// 090:0000000000666666066666660666669906669996066999990666699900066699
// 091:0000000000000000600000000000000000000000600000000000000000000000
// 093:0000000000000000000066660006666600066666000666990006699900066669
// 094:00000066000006666600066666600666990006699600066699600006990009f9
// 095:6666000066666000669900009996000099996000699900006699000099000000
// 097:00000000000000000000000000000009000009990000999900009999000099ff
// 098:00009f9900999fff99999fff99999fff9999ffff99ffffffffffffffffffffff
// 099:9000000090000000f0000000f0000000f0000000f00099909999999066666990
// 102:0000009f0000099900009999000999990099999f099999ff99999fff9999ffff
// 103:ffff9000fffff000fffff000fffff000ffff9000ffff0000fff99600ff999990
// 105:0000000000000000000000090000009f00000099000009990000999900009999
// 106:00f999009ffff900f999ff009999ff009999ff00999fff0099fff900fffff000
// 108:00000000000000000000000000000000000000090000009f000000ff000009f9
// 109:000006660000f99909ffff909f999ff0f9999ff099999ff09999ff909999ff60
// 110:99000966000099990000f9990000f9990000f9990000f9990000999900009999
// 111:f90000006f0000009f9000009ff000009ff000009fff0000ffff0000ffff0000
// 113:000099ff000099ff0000999f00009999000099990000ffff0009ffff000fffff
// 114:fffffff0ffffff00fffff000fffff000ffff9000ffff9000fffff000fffff900
// 117:000000090000000f0000009f000000ff000000ff000000ff0000009f000000f9
// 118:99999ffff99999ffff999999fff99990ffff9990fffff999ffffffffffffffff
// 119:f900999090000000000000000000000000000000000000000000000090000000
// 121:000999990099999900fff99909ffffff0fffffff0fffffff09ffffff09ffffff
// 122:9fff9000999f0000999999009999990090009900f9000000f9000000ff000000
// 124:00009ff90000fff90009fff9000fffff000fffff000fffff000fffff000fffff
// 125:999ff9009999999999999999f9990000fff90000ffff9000fffff600ffffff60
// 126:99909999999099999960f6990000f6990000f9990000ff9900009f9900009f99
// 127:ffff9000fffff000fffff000fff90000ffff0000ffff00009fff00009fff0000
// 128:00000000000000000000000000000000000000000000000f000000ff00000fff
// 129:009fff9f00fffff909fffff90fffff90ffffff00fffff900ffff9000fff90000
// 130:ffffff909ffffff909ffffff009fffff0009ffff0000ffff0009ffff000fffff
// 131:000000000000000090000000f9000000ff000000ff000000f9000000f0000000
// 132:00000000000000000000000000000000000000000996666f0999966f09990000
// 133:000000ff000000ff000000ff000009ff0099ffff9fffffffffffffffffffffff
// 134:99fffffff999ffffff999ffffff909fffff9009ffff909ffff9009fff9009fff
// 135:f9000000ff000000ff900000fff90000fff90000fff90000fff90000fff00000
// 136:0000000000000000000000000000000000000000000000000099666600999966
// 137:009fffff0009ffff0000ffff00000fff000009ff009ff99ffffff9ffffff9fff
// 138:ff900000ff900000fff00000fff00000fff90000fff90000fff90000fff00000
// 139:00000000000000000000000000000000000000000000000000000009000000ff
// 140:000fffff000fffff00ffffff00ffffff09fffff99ffffff9ffffff90fffff909
// 141:f9ffff9699fffff690ffffff909fffff009fffff09fffff99fffff90fffff900
// 142:00009f9900000fff60000fff90009fff90009fff0000ffff0000ffff0009ffff
// 143:ffff0000ffff0000fff90000fff90000fff00000fff00000ff900000ff000000
// 144:00009fff0009ffff99666ff99996000099900000099000000999000000990000
// 145:ff900000f9000000000000000000000000000000000000000000000000000000
// 146:009fffff009fffff0009fff90006600000966000099996000099999000009999
// 147:9000000000000000000000000000000000000000000000000000000090000000
// 148:0990000009000000090000000000000000000000000000000000000000000000
// 150:00009fff00009fff000009ff0000069900000660000009900000699900009999
// 151:ff900000ff000000f90000000000000000000000000000009000000099900000
// 152:0099900000990000009000000090000000000000000000000000000000000000
// 153:099f9fff00009fff00009fff000669ff00699000099990000999990000099999
// 154:ff900000f0000000f00000009000000000000000000000000000000000000000
// 155:00000fff000000ff0000066f0009966000099960000099900000999900000099
// 156:ffff9669ff969966900999600000999000000099000000000000000099000000
// 157:ffff9000ff900000000000000000000000000000000000000000000000000000
// 158:000fffff0009ffff00009ff90000066600000996000009990000999900009999
// 159:f900000090000000000000000000000000000000000000009000000099900000
// 162:0000000000000066000006660000066600000666000006690000066600000006
// 163:0000000066660000666660006699000099960000999960006999000066990000
// 166:000000060000006600000066000000660000006600000066000000000000009f
// 167:6666600066666600666990006999600099999600669990006669900099900000
// 169:0000000000000000000000660000066600000666000006660000066900000666
// 170:0000000000000000666600006666600066990000999600009999600069990000
// 172:0000000000000006000000660000006600000066000000660000006600000000
// 173:0000000066666000666666006669900069996000999996006699900066699000
// 177:0000000000000000000000000000000000000009000000090000000900000009
// 178:000009f90009ffff069f999f999f999f99ff999f9ff9999f9ff999ffff9999ff
// 179:9900000099000000f9000000ff000000ff000000ff000000f9000000f0000000
// 181:0000000000000000000000000000000000000000000000090000009900000099
// 182:00009fff000999ff009999ff099999ff99999fff9999ffff999fffff99ffffff
// 183:ff900000fff00000fff00000fff00000ff900000ff000000f996000099999000
// 184:0000000000000000000000000000000000000000000000000000000900000099
// 185:00000006000009f90009999f0099999f0999999f999999ff9999ffff999fffff
// 186:669900009900000090000000f0000000f0000000f00000009000000000000000
// 187:0000000000000000000000000000000000000000000000000000000900000099
// 188:0000009f0000999f0009999f0099999f0999999f999999ff9999ffff99ffffff
// 189:99900000ff900000fff00000fff00000fff00000fff00000ff999900ff999900
// 193:000000090000009f000000ff000009ff00009fff0000ffff0009ffff000fffff
// 194:ff999996ff999999fffffff9fffffff0fffffff0fffffff0fffffff9ffffffff
// 195:6666900099999000000000000000000000000000000000000000000090000000
// 197:0000099900000ff900009fff0000ffff0000ffff0000ffff00009fff0000f9ff
// 198:999ffff99999ff9099999900f9999000ff999000fff99900ffffff00ffffff90
// 199:0099900000000000000000000000000000000000000000000000000000000000
// 200:000009f900000ff900000ff900000fff00000fff00000fff00000fff000009ff
// 201:99fffff999fffff999ffff9099fff900999f000099990000f9999000fffff900
// 202:6666000069990000099900000000000000000000000000000000000000000000
// 203:000000990000009900000099000000990000009900000099000000090000000f
// 204:99ffffff9fffffff9fffffff9fffffff9ffffff99fffff909ffffff9ffffffff
// 205:f9669900f0000000900000000000000000000000000000000000000000000000
// 208:00000000000000000000000000000000000000000000000f0000009f000009ff
// 209:009fffff009fffff00ffffff09fffffffffffff9ffffff90fffff900ffff9000
// 210:fff9ffffff99fffff9099fff900099ff000009ff000000ff000000ff00000fff
// 211:f0000000f9000000ff900000fff00000fff90000fff90009fff00009ff900009
// 212:000000000000000000000000000000000000000096666f9f99966fff990000ff
// 213:0000ff990000fff90000ffff0009ffff99fffffffffffffffffffffffffffff9
// 214:fffffff999ffffff999ffffff909fffff9009ffff909ffff9009ffff009fffff
// 215:000000000000000090000000f9000000f9000000f9000000f9000000f0000000
// 216:000009ff0000009f0000009900000009000000000000000000000009996669ff
// 217:ffffff90fffffff9ffffffff9fffffff99ffffff999fffffffffffffffffffff
// 218:000000000000000090000000f0000000f9000000f9000000f900000090000000
// 219:0000000f0000000f0000000f0000000f0000000f0000009f0000009f000000ff
// 220:fffffffff99fffffff99ffffff999ffffff999fffff999fffff99fffff9fffff
// 221:90000000f9000000ff900000fff90000ffff0000ffff0000fff90000ff900000
// 224:00000fff00696fff999966009999600009990000099900000099000000090000
// 225:ff90000090000000000000000000000000000000000000000000000000000000
// 226:00009fff00000fff00000fff0000066600000699000009990000099900000000
// 227:ff000009f9000009900000090000000000000000990000009999000000000000
// 228:9000000000000000000000000000000000000000000000000000000000000000
// 230:009fffff009fffff0009fff90006990000066000000990000069999000999999
// 231:9000000000000000000000000000000000000000000000000000000090000000
// 232:999966ff9990009f990000999000006690000966000099600069999000999999
// 233:fffffff0fffff000999000009000000000000000000000000000000090000000
// 234:0000000000000000000000000000000000000000000000090000000000000000
// 235:00009fff000fff990006f9990966009999660009999000009990000000990000
// 236:99ffffff996ffff9966ff9009600000096000000990000000990000000000000
// 237:f900000000000000000000000000000000000000000000000000000000000000
// </TILES>

// <TILES1>
// 033:0000000000000000000000000000001000001001000100010000000000010000
// 034:0000100001000000100000100000000000000000000000000000000000000000
// 035:1000010000000000000001000000000000010100110010001000000001000000
// 036:0000000000100000000000000000011000000000001000000000000000110000
// 037:0000000000000000000000000000000000000000100100000100000010100010
// 049:0000000000001000000000000000000000000000000000000000000000000000
// 050:0100010000001000100001000001001000000000000100000000000000000100
// 051:0000000000010100000000100000110000000000001001000000101001010000
// 052:0001100010010001000011000010010000100111000001101001010100100100
// 053:0000001000000000000001000000000000010000000000010100010000000010
// 054:1000000010000000101000000000000010100000000000000000000000000000
// 066:0000000000000001000000000000000000000000000000000000000000000000
// 067:0011100010100000110100000110100101000001011010000000101000000000
// 068:0000110100000110000101000101010001010100000011001101000000000000
// 069:0000000001000000000000000000000000000000000000000000000000000000
// </TILES1>

// <TILES7>
// 000:0000000000001110000010000000100000001000000010000000000000000000
// 035:0000000000000000000000000011010001000001010000000100000000000000
// 036:0000000000000000000000000000000000000000001000000000000000001000
// 051:0100000000000000010000000000000000000000010000000000000000000000
// 052:0000000100000000000000000000000000000000000000000000000000000000
// 053:0000000000000000000000000100000000000000000000000001000000000000
// 069:0001000000000000000100000000000000100000000000000100000010000000
// 084:0000000000000010000001000000011000000010000000000000000000000000
// 085:0000000000000000000000000000000000000000100000000000000000010000
// 101:0000010000000000000000000000000000000000000000000000000000000000
// 102:0000000001001100000000000000000000000000000000000000000100000010
// 103:0000000000000000000000000000000000010010000000001011000000001000
// 104:0000000000000000000000000011000000001000000010000000100000000000
// 118:0000010100000010000010110000100100010000000000000010000001000000
// 119:0000000000000001000000000001000000000000000000000000000000000000
// 120:0000100000010000011000000100000011000000101000001000010100000000
// 121:0000000000000000000000000000000000010010000000000000000000000000
// 122:0000000000000000000000000000000001010100000000010000000000000000
// 123:0000000000000000000000000000000000000000000000001000000000000000
// 132:0000000000000000000000000000000000000000000000000000000000000011
// 133:0000000000000000000000000000000000000000000000000100000000010100
// 135:0000000000000000000000000000000000000000000000000000001000000000
// 136:0001100000000000000001000010000000000000000000100000001000000000
// 137:0000000001000000000000000001000000000000000010000000000000000000
// 139:0100000000000000000000000000000001000000000000000000000000000000
// 148:0000010000000000000010000000100000000000000010000000000000001000
// 149:0000000000000001000000000000000000000000000000000000000000000000
// 150:0000000000000000000000001000000000000000010001000000000001000000
// 151:0000000000000000010000000000000000000000000000000000000000000000
// 152:0000000100000001000000000000001000000100000000000001000000000000
// 153:0000010000000000000001000000000000000100000001000000000000000100
// 155:0100000000000000000000000000000000000000010000000000000000000000
// 164:0000010000000111000000000000000000000000000000000000000000000000
// 165:0000101001110000000000000000000000000000000000000000000000000000
// 166:0100000000000000000000000000000001000000000000000000000000000000
// 167:0000000000000010111010001000000010000000000000000100000000000000
// 168:0100000000000000000000000000000000000000000000010000000000010000
// 169:0000000000000000000100000000000000000000000000000000000000000000
// 170:0000000000000000000000000000000000000000000000100000000000000100
// 171:0000000010000000000000000000000000000000000000000000000000000000
// 182:0000000000000000010000000000000000000000000000000010000000000000
// 183:0010000000000000000010010000000000000001000000000001000000000000
// 184:0000000000000000000000000000000000000000001001000000000000000000
// 185:0000000000000000000000000000000000000000010000100000000000000000
// 186:0000000000000000000010000000000000100000000000000000000000000000
// 198:0010000000011100000000000000000000000000000000000000000000000000
// 199:1000000000000000000000000000000000000000000000000000000000000000
// </TILES7>

// <WAVES>
// 000:00000000ffffffff00000000ffffffff
// 001:0123456789abcdeffedcba9876543210
// 002:0123456789abcdef0123456789abcdef
// </WAVES>

// <SFX>
// 000:000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000304000000000
// </SFX>

// <PALETTE>
// 000:140c1c44243430346d4e4a4e854c30346524b29d38757161597dced281858595a16daa2cd2aa996dc2cadad45edeeed6
// </PALETTE>

// <PALETTE1>
// 000:000000ffffff000000000000000000000000000000000000000000000000000000000000000000000000000000000000
// </PALETTE1>

// <PALETTE7>
// 000:000000ffffff000000000000000000000000000000000000000000000000000000000000000000000000000000000000
// </PALETTE7>
