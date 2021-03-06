/**
 *
 * MACHINE GENERATED FILE. DO NOT EDIT.
 *
 * Bindings for class {{class.name}}
 *
 * This file has been generated by dub {{dub.VERSION}}.
 */
#include "dub/dub.h"
{% for h in self:headers(class) do %}
#include "{{self:header(h)}}"
{% end %}

{% if class:namespace() then %}
using namespace {{class:namespace().name}};
{% end %}

{% for method in class:methods() do %}
/** {{method:nameWithArgs()}}
 * {{method.location}}
 */
static int {{class.name}}_{{method.cname}}(lua_State *L) {
{% if method:neverThrows() then %}

  {| self:functionBody(class, method) |}
{% else %}
  try {
    {| self:functionBody(class, method) |}
  } catch (std::exception &e) {
    lua_pushfstring(L, "{{self:bindName(method)}}: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "{{self:bindName(method)}}: Unknown exception");
  }
  return dub::error(L);
{% end %}
}

{% end %}

{% if not class:method('__tostring') then %}

// --=============================================== __tostring
static int {{class.name}}___tostring(lua_State *L) {
  {| self:toStringBody(class) |}
  return 1;
}
{% end %}

// --=============================================== METHODS

static const struct luaL_Reg {{class.name}}_member_methods[] = {
{% for method in class:methods() do %}
  { {{string.format('%-15s, %-20s', '"'..self:bindName(method)..'"', class.name .. '_' .. method.cname)}} },
{% end %}
{% if not class:method('__tostring') then %}
  { {{string.format('%-15s, %-20s', '"__tostring"', class.name .. '___tostring')}} },
{% end %}
  { "deleted"      , dub::isDeleted       },
  { NULL, NULL},
};

{% if class.has_constants then %}
// --=============================================== CONSTANTS
static const struct dub::const_Reg {{class.name}}_const[] = {
{% for name, scope in class:constants() do %}
  { {{string.format('%-15s, %-20s', '"'.. self:constName(name, scope) ..'"', scope .. '::' .. name)}} },
{% end %}
  { NULL, 0},
};
{% end %}

DUB_EXPORT int luaopen_{{self:openName(class)}}(lua_State *L)
{
  // Create the metatable which will contain all the member methods
  luaL_newmetatable(L, "{{self:libName(class)}}");
  // <mt>
{% if class.has_constants then %}
  // register class constants
  dub::register_const(L, {{class.name}}_const);
{% end %}

  // register member methods
  dub::fregister(L, {{ class.name }}_member_methods);
  // setup meta-table
  dub::setup(L, "{{self:libName(class)}}");
  // <mt>
  return 1;
}
