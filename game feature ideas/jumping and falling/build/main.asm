;--------------------------------------------------------
; File Created by SDCC : free open source ISO C Compiler 
; Version 4.2.2 #13350 (MINGW64)
;--------------------------------------------------------
	.module main
	.optsdcc -msm83
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _jump
	.globl _collisionDetect
	.globl _betterDelay
	.globl _set_sprite_data
	.globl _set_bkg_tiles
	.globl _set_bkg_data
	.globl _wait_vbl_done
	.globl _joypad
	.globl _floorYpos
	.globl _gravity
	.globl _acceleration
	.globl _jumping
	.globl _characterNum
	.globl _playerStats
	.globl _Face
	.globl _Tilemap
	.globl _bg
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
G$bg$0_0$0==.
_bg::
	.ds 720
G$Tilemap$0_0$0==.
_Tilemap::
	.ds 128
G$Face$0_0$0==.
_Face::
	.ds 32
G$playerStats$0_0$0==.
_playerStats::
	.ds 4
G$characterNum$0_0$0==.
_characterNum::
	.ds 1
G$jumping$0_0$0==.
_jumping::
	.ds 1
G$acceleration$0_0$0==.
_acceleration::
	.ds 1
G$gravity$0_0$0==.
_gravity::
	.ds 1
G$floorYpos$0_0$0==.
_floorYpos::
	.ds 1
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area _DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _HOME
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
	G$betterDelay$0$0	= .
	.globl	G$betterDelay$0$0
	C$main.c$14$0_0$105	= .
	.globl	C$main.c$14$0_0$105
;main.c:14: void betterDelay(uint8_t numloops) {
;	---------------------------------
; Function betterDelay
; ---------------------------------
_betterDelay::
	ld	c, a
	C$main.c$16$2_0$105	= .
	.globl	C$main.c$16$2_0$105
;main.c:16: for(i = 0; i < numloops; i++) {
	ld	b, #0x00
00103$:
	ld	a, b
	sub	a, c
	ret	NC
	C$main.c$17$3_0$106	= .
	.globl	C$main.c$17$3_0$106
;main.c:17: wait_vbl_done();
	call	_wait_vbl_done
	C$main.c$16$2_0$105	= .
	.globl	C$main.c$16$2_0$105
;main.c:16: for(i = 0; i < numloops; i++) {
	inc	b
	C$main.c$20$2_0$105	= .
	.globl	C$main.c$20$2_0$105
;main.c:20: }
	C$main.c$20$2_0$105	= .
	.globl	C$main.c$20$2_0$105
	XG$betterDelay$0$0	= .
	.globl	XG$betterDelay$0$0
	jr	00103$
	G$collisionDetect$0$0	= .
	.globl	G$collisionDetect$0$0
	C$main.c$22$2_0$108	= .
	.globl	C$main.c$22$2_0$108
;main.c:22: int8_t collisionDetect(uint8_t projectedYpos) {
;	---------------------------------
; Function collisionDetect
; ---------------------------------
_collisionDetect::
	ld	c, a
	C$main.c$23$1_0$108	= .
	.globl	C$main.c$23$1_0$108
;main.c:23: if (projectedYpos > floorYpos) {
	ld	a, (#_floorYpos)
	sub	a, c
	jr	NC, 00102$
	C$main.c$24$2_0$109	= .
	.globl	C$main.c$24$2_0$109
;main.c:24: return 1;
	ld	a, #0x01
	ret
00102$:
	C$main.c$26$1_0$108	= .
	.globl	C$main.c$26$1_0$108
;main.c:26: return -1;
	ld	a, #0xff
	C$main.c$27$1_0$108	= .
	.globl	C$main.c$27$1_0$108
;main.c:27: }
	C$main.c$27$1_0$108	= .
	.globl	C$main.c$27$1_0$108
	XG$collisionDetect$0$0	= .
	.globl	XG$collisionDetect$0$0
	ret
	G$jump$0$0	= .
	.globl	G$jump$0$0
	C$main.c$29$1_0$111	= .
	.globl	C$main.c$29$1_0$111
;main.c:29: void jump(uint8_t characterNum, uint8_t charStats[4]) {
;	---------------------------------
; Function jump
; ---------------------------------
_jump::
	add	sp, #-4
	ldhl	sp,	#3
	ld	(hl-), a
	dec	hl
	ld	a, e
	ld	(hl+), a
	C$main.c$33$3_0$111	= .
	.globl	C$main.c$33$3_0$111
;main.c:33: charStats[3] = 15;
	ld	a, d
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	inc	de
	inc	de
	inc	de
	C$main.c$31$1_0$111	= .
	.globl	C$main.c$31$1_0$111
;main.c:31: if (!jumping) {
	ld	hl, #_jumping
	ld	a, (hl)
	or	a, a
	jr	NZ, 00102$
	C$main.c$32$2_0$112	= .
	.globl	C$main.c$32$2_0$112
;main.c:32: jumping = 1;
	ld	(hl), #0x01
	C$main.c$33$2_0$112	= .
	.globl	C$main.c$33$2_0$112
;main.c:33: charStats[3] = 15;
	ld	a, #0x0f
	ld	(de), a
00102$:
	C$main.c$36$1_0$111	= .
	.globl	C$main.c$36$1_0$111
;main.c:36: charStats[3] = charStats[3] - gravity;
	ld	a, (de)
	ld	hl, #_gravity
	sub	a, (hl)
	ldhl	sp,	#0
	ld	(hl), a
	C$main.c$38$1_0$111	= .
	.globl	C$main.c$38$1_0$111
;main.c:38: charStats[1] = charStats[1] - charStats[3];
	ld	a, (hl+)
	ld	(de), a
	ld	a, (hl+)
	ld	c, a
	ld	a, (hl-)
	dec	hl
	ld	b, a
	inc	bc
	ld	a, (bc)
	sub	a, (hl)
	ld	(hl), a
	ld	a, (hl)
	ld	(bc), a
	C$main.c$40$1_0$111	= .
	.globl	C$main.c$40$1_0$111
;main.c:40: if  (collisionDetect(charStats[1]) == 1) {
	push	bc
	push	de
	ld	a, (hl)
	call	_collisionDetect
	pop	de
	pop	bc
	dec	a
	jr	NZ, 00104$
	C$main.c$41$2_0$113	= .
	.globl	C$main.c$41$2_0$113
;main.c:41: jumping = 0;
	ld	hl, #_jumping
	ld	(hl), #0x00
	C$main.c$42$2_0$113	= .
	.globl	C$main.c$42$2_0$113
;main.c:42: charStats[3] = 0;
	xor	a, a
	ld	(de), a
	C$main.c$43$2_0$113	= .
	.globl	C$main.c$43$2_0$113
;main.c:43: charStats[1] = floorYpos;
	ld	a, (#_floorYpos)
	ld	(bc), a
00104$:
;main.c:46: move_sprite(characterNum, charStats[0], charStats[1]);
	ld	a, (bc)
	ld	b, a
	ldhl	sp,#1
	ld	a, (hl+)
	ld	e, a
;c:/gbdk/include/gb/gb.h:1675: OAM_item_t * itm = &shadow_OAM[nb];
	ld	a, (hl+)
	ld	d, a
	ld	a, (de)
	ld	c, a
	ld	a, (hl)
	ld	e, #0x00
	ld	l, a
	ld	h, e
	add	hl, hl
	add	hl, hl
	ld	de, #_shadow_OAM
	add	hl, de
;c:/gbdk/include/gb/gb.h:1676: itm->y=y, itm->x=x;
	ld	(hl), b
	inc	hl
	ld	(hl), c
	C$main.c$46$3_0$111	= .
	.globl	C$main.c$46$3_0$111
;main.c:46: move_sprite(characterNum, charStats[0], charStats[1]);
	C$main.c$48$3_0$111	= .
	.globl	C$main.c$48$3_0$111
;main.c:48: }
	add	sp, #4
	C$main.c$48$3_0$111	= .
	.globl	C$main.c$48$3_0$111
	XG$jump$0$0	= .
	.globl	XG$jump$0$0
	ret
	G$main$0$0	= .
	.globl	G$main$0$0
	C$main.c$50$3_0$117	= .
	.globl	C$main.c$50$3_0$117
;main.c:50: void main() {
;	---------------------------------
; Function main
; ---------------------------------
_main::
	dec	sp
	C$main.c$52$1_0$117	= .
	.globl	C$main.c$52$1_0$117
;main.c:52: set_sprite_data(0, 2, Face);
	ld	de, #_Face
	push	de
	ld	hl, #0x200
	push	hl
	call	_set_sprite_data
	add	sp, #4
	C$main.c$54$1_0$117	= .
	.globl	C$main.c$54$1_0$117
;main.c:54: set_bkg_data(0, 8, Tilemap);
	ld	de, #_Tilemap
	push	de
	ld	hl, #0x800
	push	hl
	call	_set_bkg_data
	add	sp, #4
	C$main.c$55$1_0$117	= .
	.globl	C$main.c$55$1_0$117
;main.c:55: set_bkg_tiles(0, 0, 40, 18, bg);
	ld	de, #_bg
	push	de
	ld	hl, #0x1228
	push	hl
	xor	a, a
	rrca
	push	af
	call	_set_bkg_tiles
	add	sp, #6
;main.c:57: set_sprite_tile(characterNum, 0);
	ld	hl, #_characterNum
;c:/gbdk/include/gb/gb.h:1602: shadow_OAM[nb].tile=tile;
	ld	l, (hl)
	ld	bc, #_shadow_OAM+0
;	spillPairReg hl
;	spillPairReg hl
	ld	h, #0x00
;	spillPairReg hl
;	spillPairReg hl
	add	hl, hl
	add	hl, hl
	add	hl, bc
	inc	hl
	inc	hl
	ld	(hl), #0x00
;main.c:58: move_sprite(characterNum, playerStats[0], playerStats[1]);
	ld	hl, #(_playerStats + 1)
	ld	b, (hl)
	ld	hl, #_playerStats
	ld	c, (hl)
	ld	hl, #_characterNum
;c:/gbdk/include/gb/gb.h:1675: OAM_item_t * itm = &shadow_OAM[nb];
	ld	l, (hl)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, #0x00
;	spillPairReg hl
;	spillPairReg hl
	add	hl, hl
	add	hl, hl
	ld	de, #_shadow_OAM
	add	hl, de
;c:/gbdk/include/gb/gb.h:1676: itm->y=y, itm->x=x;
	ld	a, b
	ld	(hl+), a
	ld	(hl), c
	C$main.c$60$1_0$117	= .
	.globl	C$main.c$60$1_0$117
;main.c:60: SHOW_BKG;
	ldh	a, (_LCDC_REG + 0)
	or	a, #0x01
	ldh	(_LCDC_REG + 0), a
	C$main.c$61$1_0$117	= .
	.globl	C$main.c$61$1_0$117
;main.c:61: SHOW_SPRITES;
	ldh	a, (_LCDC_REG + 0)
	or	a, #0x02
	ldh	(_LCDC_REG + 0), a
	C$main.c$62$1_0$117	= .
	.globl	C$main.c$62$1_0$117
;main.c:62: DISPLAY_ON;
	ldh	a, (_LCDC_REG + 0)
	or	a, #0x80
	ldh	(_LCDC_REG + 0), a
	C$main.c$64$1_0$117	= .
	.globl	C$main.c$64$1_0$117
;main.c:64: while (1) {
00112$:
	C$main.c$65$2_0$118	= .
	.globl	C$main.c$65$2_0$118
;main.c:65: if (joypad()) {
	call	_joypad
	or	a, a
	jr	Z, 00107$
	C$main.c$67$3_0$119	= .
	.globl	C$main.c$67$3_0$119
;main.c:67: if (joypad() & J_LEFT) {
	call	_joypad
	C$main.c$68$1_0$117	= .
	.globl	C$main.c$68$1_0$117
;main.c:68: acceleration = -playerStats[2];
	ld	bc, #_playerStats + 2
	C$main.c$67$3_0$119	= .
	.globl	C$main.c$67$3_0$119
;main.c:67: if (joypad() & J_LEFT) {
	bit	1, a
	jr	Z, 00104$
	C$main.c$68$4_0$120	= .
	.globl	C$main.c$68$4_0$120
;main.c:68: acceleration = -playerStats[2];
	ld	a, (bc)
	ld	c, a
	xor	a, a
	sub	a, c
	ld	(#_acceleration),a
	jr	00105$
00104$:
	C$main.c$69$3_0$119	= .
	.globl	C$main.c$69$3_0$119
;main.c:69: } else if (joypad() & J_RIGHT) {
	call	_joypad
	rrca
	jr	NC, 00105$
	C$main.c$70$4_0$121	= .
	.globl	C$main.c$70$4_0$121
;main.c:70: acceleration = playerStats[2];
	ld	a, (bc)
	ld	(#_acceleration),a
00105$:
	C$main.c$72$3_0$119	= .
	.globl	C$main.c$72$3_0$119
;main.c:72: playerStats[0] = playerStats[0] + acceleration;
	ld	a, (#_playerStats + 0)
	ld	hl, #_acceleration
	add	a, (hl)
	ld	(#_playerStats),a
;main.c:73: move_sprite(characterNum, playerStats[0], playerStats[1]);
	ld	hl, #(_playerStats + 1)
	ld	c, (hl)
	ldhl	sp,	#0
	ld	(hl), a
	ld	hl, #_characterNum
	ld	b, (hl)
;c:/gbdk/include/gb/gb.h:1675: OAM_item_t * itm = &shadow_OAM[nb];
	ld	de, #_shadow_OAM+0
	ld	h, #0x00
;	spillPairReg hl
;	spillPairReg hl
	ld	l, b
	add	hl, hl
	add	hl, hl
	add	hl, de
	ld	e, l
	ld	d, h
;c:/gbdk/include/gb/gb.h:1676: itm->y=y, itm->x=x;
	ld	a, c
	ld	(de), a
	inc	de
	ldhl	sp,	#0
	ld	a, (hl)
	ld	(de), a
	C$main.c$73$2_0$118	= .
	.globl	C$main.c$73$2_0$118
;main.c:73: move_sprite(characterNum, playerStats[0], playerStats[1]);
00107$:
	C$main.c$77$2_0$118	= .
	.globl	C$main.c$77$2_0$118
;main.c:77: if (joypad() & J_A || jumping == 1) {
	call	_joypad
	bit	4, a
	jr	NZ, 00108$
	ld	a, (#_jumping)
	dec	a
	jr	NZ, 00109$
00108$:
	C$main.c$78$3_0$122	= .
	.globl	C$main.c$78$3_0$122
;main.c:78: jump(characterNum, playerStats);
	ld	de, #_playerStats
	ld	a, (#_characterNum)
	call	_jump
00109$:
	C$main.c$81$2_0$118	= .
	.globl	C$main.c$81$2_0$118
;main.c:81: betterDelay(2);
	ld	a, #0x02
	call	_betterDelay
	C$main.c$82$2_0$118	= .
	.globl	C$main.c$82$2_0$118
;main.c:82: acceleration = 0;
	ld	hl, #_acceleration
	ld	(hl), #0x00
	jr	00112$
	C$main.c$85$1_0$117	= .
	.globl	C$main.c$85$1_0$117
;main.c:85: }
	inc	sp
	C$main.c$85$1_0$117	= .
	.globl	C$main.c$85$1_0$117
	XG$main$0$0	= .
	.globl	XG$main$0$0
	ret
	.area _CODE
	.area _INITIALIZER
Fmain$__xinit_bg$0_0$0 == .
__xinit__bg:
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x04	; 4
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x04	; 4
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x04	; 4
	.db #0x00	; 0
	.db #0x08	; 8
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x02	; 2
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x08	; 8
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x02	; 2
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x02	; 2
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x08	; 8
	.db #0x08	; 8
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x02	; 2
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x02	; 2
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x02	; 2
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x02	; 2
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x06	; 6
	.db #0x06	; 6
	.db #0x06	; 6
	.db #0x06	; 6
	.db #0x03	; 3
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x02	; 2
	.db #0x05	; 5
	.db #0x05	; 5
	.db #0x05	; 5
	.db #0x05	; 5
	.db #0x05	; 5
	.db #0x05	; 5
	.db #0x03	; 3
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x02	; 2
	.db #0x06	; 6
	.db #0x06	; 6
	.db #0x06	; 6
	.db #0x06	; 6
	.db #0x06	; 6
	.db #0x06	; 6
	.db #0x06	; 6
	.db #0x06	; 6
	.db #0x06	; 6
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x08	; 8
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x04	; 4
	.db #0x08	; 8
	.db #0x08	; 8
	.db #0x08	; 8
	.db #0x04	; 4
	.db #0x08	; 8
	.db #0x08	; 8
	.db #0x08	; 8
	.db #0x04	; 4
	.db #0x08	; 8
	.db #0x08	; 8
	.db #0x08	; 8
	.db #0x04	; 4
	.db #0x08	; 8
	.db #0x08	; 8
	.db #0x08	; 8
	.db #0x04	; 4
	.db #0x08	; 8
	.db #0x08	; 8
	.db #0x08	; 8
	.db #0x04	; 4
	.db #0x08	; 8
	.db #0x08	; 8
	.db #0x08	; 8
	.db #0x04	; 4
	.db #0x08	; 8
	.db #0x08	; 8
	.db #0x08	; 8
	.db #0x04	; 4
	.db #0x08	; 8
	.db #0x08	; 8
	.db #0x08	; 8
	.db #0x04	; 4
	.db #0x08	; 8
	.db #0x08	; 8
	.db #0x08	; 8
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
Fmain$__xinit_Tilemap$0_0$0 == .
__xinit__Tilemap:
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0xff	; 255
	.db #0xff	; 255
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0xff	; 255
	.db #0xff	; 255
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0xff	; 255
	.db #0xff	; 255
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0xff	; 255
	.db #0xff	; 255
	.db #0x11	; 17
	.db #0x11	; 17
	.db #0x11	; 17
	.db #0x11	; 17
	.db #0x11	; 17
	.db #0x11	; 17
	.db #0xff	; 255
	.db #0xff	; 255
	.db #0x80	; 128
	.db #0x80	; 128
	.db #0x80	; 128
	.db #0x80	; 128
	.db #0x80	; 128
	.db #0x80	; 128
	.db #0xff	; 255
	.db #0xff	; 255
	.db #0x88	; 136
	.db #0x88	; 136
	.db #0x88	; 136
	.db #0x88	; 136
	.db #0x88	; 136
	.db #0x88	; 136
	.db #0xaa	; 170
	.db #0x00	; 0
	.db #0x55	; 85	'U'
	.db #0x00	; 0
	.db #0xaa	; 170
	.db #0x00	; 0
	.db #0x55	; 85	'U'
	.db #0x00	; 0
	.db #0xaa	; 170
	.db #0x00	; 0
	.db #0x55	; 85	'U'
	.db #0x00	; 0
	.db #0xaa	; 170
	.db #0x00	; 0
	.db #0x55	; 85	'U'
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0xff	; 255
	.db #0xff	; 255
	.db #0xaa	; 170
	.db #0xff	; 255
	.db #0x3f	; 63
	.db #0xc0	; 192
	.db #0xaa	; 170
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0xcc	; 204
	.db #0xff	; 255
	.db #0x32	; 50	'2'
	.db #0xcd	; 205
	.db #0xff	; 255
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0xff	; 255
	.db #0x00	; 0
	.db #0xff	; 255
	.db #0x00	; 0
	.db #0xff	; 255
	.db #0x00	; 0
Fmain$__xinit_Face$0_0$0 == .
__xinit__Face:
	.db #0x7e	; 126
	.db #0x7e	; 126
	.db #0x81	; 129
	.db #0xff	; 255
	.db #0xa5	; 165
	.db #0xff	; 255
	.db #0xe5	; 229
	.db #0xbf	; 191
	.db #0xfd	; 253
	.db #0xa7	; 167
	.db #0xff	; 255
	.db #0x81	; 129
	.db #0x7e	; 126
	.db #0x42	; 66	'B'
	.db #0x3c	; 60
	.db #0x3c	; 60
	.db #0x7e	; 126
	.db #0x7e	; 126
	.db #0x81	; 129
	.db #0xff	; 255
	.db #0xa5	; 165
	.db #0xff	; 255
	.db #0xa5	; 165
	.db #0xff	; 255
	.db #0xc1	; 193
	.db #0xbf	; 191
	.db #0xff	; 255
	.db #0x81	; 129
	.db #0x7e	; 126
	.db #0x42	; 66	'B'
	.db #0x3c	; 60
	.db #0x3c	; 60
Fmain$__xinit_playerStats$0_0$0 == .
__xinit__playerStats:
	.db #0x0a	; 10
	.db #0x87	; 135
	.db #0x03	; 3
	.db #0x00	; 0
Fmain$__xinit_characterNum$0_0$0 == .
__xinit__characterNum:
	.db #0x00	; 0
Fmain$__xinit_jumping$0_0$0 == .
__xinit__jumping:
	.db #0x00	; 0
Fmain$__xinit_acceleration$0_0$0 == .
__xinit__acceleration:
	.db #0x00	; 0
Fmain$__xinit_gravity$0_0$0 == .
__xinit__gravity:
	.db #0x02	; 2
Fmain$__xinit_floorYpos$0_0$0 == .
__xinit__floorYpos:
	.db #0x87	; 135
	.area _CABS (ABS)
