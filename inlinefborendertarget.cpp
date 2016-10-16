#include "inlinefborendertarget.h"

InlineFboRenderTarget::InlineFboRenderTarget() {

    _gl.initializeOpenGLFunctions();
}

GLint&
InlineFboRenderTarget::fbo() {

    return _fbo;
}

void
InlineFboRenderTarget::doPrepare() const {}

void
InlineFboRenderTarget::doBind() const    { _gl.glBindFramebuffer(GL_FRAMEBUFFER,_fbo); }

void
InlineFboRenderTarget::doUnbind() const  { _gl.glBindFramebuffer(GL_FRAMEBUFFER,0x0); }

void
InlineFboRenderTarget::doResize()        {}
