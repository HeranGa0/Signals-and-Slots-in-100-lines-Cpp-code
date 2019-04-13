// Learn cc.Class:
//  - [Chinese] http://docs.cocos.com/creator/manual/zh/scripting/class.html
//  - [English] http://www.cocos2d-x.org/docs/creator/en/scripting/class.html
// Learn Attribute:
//  - [Chinese] http://docs.cocos.com/creator/manual/zh/scripting/reference/attributes.html
//  - [English] http://www.cocos2d-x.org/docs/creator/en/scripting/reference/attributes.html
// Learn life-cycle callbacks:
//  - [Chinese] http://docs.cocos.com/creator/manual/zh/scripting/life-cycle-callbacks.html
//  - [English] http://www.cocos2d-x.org/docs/creator/en/scripting/life-cycle-callbacks.html

cc.Class({
    extends: cc.Component,

    properties: {
        force:null,
        // foo: {
        //     // ATTRIBUTES:
        //     default: null,        // The default value will be used only when the component attaching
        //                           // to a node for the first time
        //     type: cc.SpriteFrame, // optional, default is typeof default
        //     serializable: true,   // optional, default is true
        // },
        // bar: {
        //     get () {
        //         return this._bar;
        //     },
        //     set (value) {
        //         this._bar = value;
        //     }
        // },
    },

    // LIFE-CYCLE CALLBACKS:

    onLoad () {
        this.force = cc.v2(0,0);
        let g = this.getComponent(cc.Graphics);
        g.rect(-50,-7.5,100,15);
        g.fill();
        cc.systemEvent.on(cc.SystemEvent.EventType.KEY_DOWN, this.onKeyDown, this);
        cc.systemEvent.on(cc.SystemEvent.EventType.KEY_UP, this.onKeyUp, this);
    },
    onKeyDown (event) {
        // set a flag when key pressed
        //let pos = this.node.getPosition();
        //console.log(pos.x);
        switch(event.keyCode) {
            case cc.macro.KEY.s:
                this.force = cc.v2(-500,0);
                break;
            case cc.macro.KEY.w:
                this.force = cc.v2(500,0);
                break;
        }
        //cc.log(this.node.position);
        //let pos = this.node.getPosition();
        //console.log(pos.x);
    },

    onKeyUp (event) {
        // unset a flag when key released
        let force = 50;
        switch(event.keyCode) {
            case cc.macro.KEY.s:
                this.force = cc.v2(0,0);
                break;
            case cc.macro.KEY.w:
                this.force = cc.v2(0,0);
                break;
        }
    },
    start () {

    },
    update: function (dt) {
        //console.log(this.force.x);
        this.getComponent(cc.RigidBody).applyForceToCenter(this.force);
    },
    onDestroy () {
        // 取消键盘输入监听
        cc.systemEvent.off(cc.SystemEvent.EventType.KEY_DOWN, this.onKeyDown, this);
        cc.systemEvent.off(cc.SystemEvent.EventType.KEY_UP, this.onKeyUp, this);
    },
    // update (dt) {},
});
