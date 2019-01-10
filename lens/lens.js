// script: javascript

var buf = []

var an1 = 0
var an2 = 0
const radx = 80
const rady = 30

function TIC () {
  flushBuffer(120 + Math.cos(an1)*radx,
    68 + Math.sin(an2)*rady,
    30, 30, -4, -4);
  an1 += 0.07;
  an2 += 0.13;
}

cls(0)
// for (var i = 0; i < 100; i++) {
//   line(Math.random()*240, Math.random()*136, Math.random()*240, Math.random()*136, 1);
// }
map(0, 0, 30, 17, 0, 0, 1)


for (var y = 0; y < 136; y++) {
  for (var x = 0; x < 240; x++) {
    buf.push(pix(x, y))
  }
}

function getLensBufferPixel(x, y, lensX, lensY, lensW, lensH, shiftX, shiftY) {
  var nx = x;
  var ny = y;
  var xs = x - lensX;
  var ys = y - lensY;
  var rs = lensW*lensH;
  if (xs*xs + ys*ys < rs) {
    ny = y + shiftY;
    nx = x + shiftX;
  }
  return buf[nx + ny*240]
}


function flushBuffer(lensX, lensY, lensW, lensH, shiftX, shiftY) {
  for (var y = 0; y < 136; y++) {
    for (var x = 0; x < 240; x++) {
      const color = getLensBufferPixel(x, y, lensX, lensY,
        lensW, lensH, shiftX, shiftY);
      pix(x, y, color)
    }
  }
}
