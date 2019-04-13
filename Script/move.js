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
        points:[],
        chainCollider:null,
        isActivated: false,
        graphic: null,
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

    // onLoad () {},

    start () {

    },

    onLoad: function () {
        console.log(1);
        this.node.on(cc.Node.EventType.MOUSE_MOVE, this.onMove,this);
        this.node.on(cc.Node.EventType.MOUSE_UP, this.onUp,this);
        this.node.on(cc.Node.EventType.MOUSE_DOWN, this.onDown,this);

        cc.director.getPhysicsManager().enabled = true;
        this.graphic = this.getComponent(cc.Graphics);
        this.chainCollider = this.getComponent(cc.PhysicsChainCollider);
        //this.chainCollider.points = [cc.v2(200,0),cc.v2(200,-300),cc.v2(200,0),cc.v2(200,0)];
        //this.test(cc.v2(100,100),cc.v2(200,200));
        //cc.systemEvent.on(cc.Node.EventType.MOUSE_MOVE, this.onMove, this);
        // cc.systemEvent.on(cc.Node.EventType.MOUSE_UP, this.onEnd, this);
        // cc.systemEvent.on(cc.SystemEvent.EventType.KEY_DOWN, this.onKeyDown, this);
    },
    onMove: function(event) {
        if (this.isActivated) {
            let pos = event.getLocation();
            pos = cc.v2(pos.x-this.node.width/4,pos.y-this.node.height/2);
            let lastPoint = this.points[this.points.length-1];
            this.points.push(pos);
            this.graphic.moveTo(lastPoint.x,lastPoint.y);
            this.graphic.lineTo(pos.x,pos.y);
            this.graphic.stroke();
            console.log(pos.x,pos.y);
        }
    },
    onUp: function(event) {
        this.isActivated= false;
        //this.chainCollider.points = [cc.v2(200,0),cc.v2(200,-300),cc.v2(200,0),cc.v2(200,0)];
        this.chainCollider.points = this.points;
        //this.chainCollider.points = [cc.v2(0,0),cc.v2(0,-300),cc.v2(0,0),cc.v2(0,0)];
        this.chainCollider.apply();
        //this.chainCollider.onLoad();
        //this.node.addComponent(cc.PhysicsChainCollider);
       // this.node.getComponent(cc.PhysicsChainCollider).points = [cc.v2(0,0),cc.v2(0,-0),cc.v2(100,-0),cc.v2(100,0)];
       // this.node.getComponent(cc.PhysicsChainCollider).enabled = true;
       // this.node.getComponent(cc.CircleCollider).node.setScale(5);
        //this.chainCollider.points = [cc.v2(200,0),cc.v2(200,-300),cc.v2(400,0),cc.v2(400,-300)];
        //this.chainCollider.enabled = true;
        this.points = [];
        //console.log('Crazy start:',this.chainCollider.x,this.chainCollider.y);

    },
    onDown: function(event) {
        this.isActivated= true;
        let pos = event.getLocation();
        pos = cc.v2(pos.x-this.node.width/4,pos.y-this.node.height/2);
        this.points.push(pos);
        console.log('onDown!');
    },

    onDestroy () {
        // 取消键盘输入监听
        //cc.systemEvent.off(ccc.Node.EventType.MOUSE_MOVE, this.onMove, this);
        //cc.systemEvent.off(cc.Node.EventType.MOUSE_UP, this.onEnd, this);
    },
    // update (dt) {},
});
